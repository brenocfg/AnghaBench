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
 int NX509_SIG ; 
 size_t SIGABRT ; 
 size_t SIGFPE ; 
 size_t SIGILL ; 
 size_t SIGINT ; 
 size_t SIGSEGV ; 
 size_t SIGTERM ; 
 int SIGUSR1 ; 
 int SIGUSR2 ; 
 int /*<<< orphan*/ * savsig ; 
 int /*<<< orphan*/  sigaction (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void popsig(void)
{
#  ifdef OPENSSL_SYS_WIN32
    signal(SIGABRT, savsig[SIGABRT]);
    signal(SIGFPE, savsig[SIGFPE]);
    signal(SIGILL, savsig[SIGILL]);
    signal(SIGINT, savsig[SIGINT]);
    signal(SIGSEGV, savsig[SIGSEGV]);
    signal(SIGTERM, savsig[SIGTERM]);
#  else
    int i;
    for (i = 1; i < NX509_SIG; i++) {
#   ifdef SIGUSR1
        if (i == SIGUSR1)
            continue;
#   endif
#   ifdef SIGUSR2
        if (i == SIGUSR2)
            continue;
#   endif
#   ifdef SIGACTION
        sigaction(i, &savsig[i], NULL);
#   else
        signal(i, savsig[i]);
#   endif
    }
#  endif
}