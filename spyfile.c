/*
	Monitors file changes
	(c) 2006-2007 Vladimir Dubrovin, 3APA3A
	http://securityvulns.com/
	http://securityvulns.ru/
*/

#include <stdio.h>
#include <windows.h>

int main(int argc, char * argv[]){
	HANDLE h;
	int n;
	char buf[10240];
	if(argc != 2) {
		printf(
"Usage: %s <file_path>\n"
" Monitor file cheanges\n"
" keep access to the file even after file permissions have changed\n"
"(c) Vladimir Dubrovin, 3APA3A\n"
" http://securityvulns.com\n"
" http://securityvulns.ru\n",
 argv[0]);
		return 1;
		
	}
	for(;(
		h=CreateFile(argv[1], 
					 GENERIC_READ, 
					 FILE_SHARE_WRITE|FILE_SHARE_READ|FILE_SHARE_DELETE,
					 NULL,
					 OPEN_ALWAYS,
					 FILE_FLAG_BACKUP_SEMANTICS,
					 NULL
					 )
		) == INVALID_HANDLE_VALUE;);
	for(;;){
		SetFilePointer(h, 0, 0, FILE_CURRENT);
		n = 0;
		ReadFile(h, buf, 10240, (LPDWORD)&n, NULL);
		if(n>0) write(1, buf, n);
/*
	we need to sleep here or we get 0 data after file size have changed but
	data is not actually written
*/
		Sleep(1000);
	}
	return 0;
}
