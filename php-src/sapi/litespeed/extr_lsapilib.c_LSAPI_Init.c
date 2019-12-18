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

/* Variables and functions */
 int LSAPI_InitRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSAPI_SOCK_FILENO ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/  SIG_IGN ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlsym (void*,char*) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int g_inited ; 
 int /*<<< orphan*/  g_req ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  lsapi_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsapi_sigpipe ; 
 int /*<<< orphan*/  lsapi_siguser1 ; 
 int /*<<< orphan*/  pthread_atfork_func ; 
 int /*<<< orphan*/  s_ppid ; 
 scalar_t__* s_secret ; 
 int /*<<< orphan*/  s_uid ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int LSAPI_Init(void)
{
    if ( !g_inited )
    {
        s_uid = geteuid();
        s_secret[0] = 0;
        lsapi_signal(SIGPIPE, lsapi_sigpipe);
        lsapi_signal(SIGUSR1, lsapi_siguser1);

#if defined(SIGXFSZ) && defined(SIG_IGN)
        signal(SIGXFSZ, SIG_IGN);
#endif
        /* let STDOUT function as STDERR,
           just in case writing to STDOUT directly */
        dup2( 2, 1 );
        if ( LSAPI_InitRequest( &g_req, LSAPI_SOCK_FILENO ) == -1 )
            return -1;
        g_inited = 1;
        s_ppid = getppid();
        void *pthread_lib = dlopen("libpthread.so", RTLD_LAZY);
        if (pthread_lib)
            pthread_atfork_func = dlsym(pthread_lib, "pthread_atfork");

    }
    return 0;
}