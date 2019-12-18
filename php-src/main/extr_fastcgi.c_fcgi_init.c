#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ zend_long ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sa_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOTCONN ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAKEWORD (int,int /*<<< orphan*/ ) ; 
 int PIPE_READMODE_BYTE ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetNamedPipeHandleState (scalar_t__,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WSAGetLastError () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ATOL (scalar_t__,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ fcgi_accept_mutex ; 
 int /*<<< orphan*/  fcgi_free_mgmt_var_cb ; 
 int /*<<< orphan*/  fcgi_mgmt_vars ; 
 int /*<<< orphan*/  fcgi_set_mgmt_var (char*,int,char*,int) ; 
 int /*<<< orphan*/  fcgi_setup_signals () ; 
 int /*<<< orphan*/  fcgi_shutdown_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* getenv (char*) ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int is_fastcgi ; 
 int is_initialized ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int fcgi_init(void)
{
	if (!is_initialized) {
#ifndef _WIN32
		sa_t sa;
		socklen_t len = sizeof(sa);
#endif
		zend_hash_init(&fcgi_mgmt_vars, 8, NULL, fcgi_free_mgmt_var_cb, 1);
		fcgi_set_mgmt_var("FCGI_MPXS_CONNS", sizeof("FCGI_MPXS_CONNS")-1, "0", sizeof("0")-1);

		is_initialized = 1;
#ifdef _WIN32
# if 0
		/* TODO: Support for TCP sockets */
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2,0), &wsaData)) {
			fprintf(stderr, "Error starting Windows Sockets.  Error: %d", WSAGetLastError());
			return 0;
		}
# endif
		if ((GetStdHandle(STD_OUTPUT_HANDLE) == INVALID_HANDLE_VALUE) &&
		    (GetStdHandle(STD_ERROR_HANDLE)  == INVALID_HANDLE_VALUE) &&
		    (GetStdHandle(STD_INPUT_HANDLE)  != INVALID_HANDLE_VALUE)) {
			char *str;
			DWORD pipe_mode = PIPE_READMODE_BYTE | PIPE_WAIT;
			HANDLE pipe = GetStdHandle(STD_INPUT_HANDLE);

			SetNamedPipeHandleState(pipe, &pipe_mode, NULL, NULL);

			str = getenv("_FCGI_SHUTDOWN_EVENT_");
			if (str != NULL) {
				zend_long ev;
				HANDLE shutdown_event;

				ZEND_ATOL(ev, str);
				shutdown_event = (HANDLE) ev;
				if (!CreateThread(NULL, 0, fcgi_shutdown_thread,
				                  shutdown_event, 0, NULL)) {
					return -1;
				}
			}
			str = getenv("_FCGI_MUTEX_");
			if (str != NULL) {
				zend_long mt;
				ZEND_ATOL(mt, str);
				fcgi_accept_mutex = (HANDLE) mt;
			}
			return is_fastcgi = 1;
		} else {
			return is_fastcgi = 0;
		}
#else
		errno = 0;
		if (getpeername(0, (struct sockaddr *)&sa, &len) != 0 && errno == ENOTCONN) {
			fcgi_setup_signals();
			return is_fastcgi = 1;
		} else {
			return is_fastcgi = 0;
		}
#endif
	}
	return is_fastcgi;
}