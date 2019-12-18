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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int NX509_SIG ; 
 size_t SIGABRT ; 
 size_t SIGFPE ; 
 size_t SIGILL ; 
 size_t SIGINT ; 
 int SIGKILL ; 
 size_t SIGSEGV ; 
 size_t SIGTERM ; 
 int SIGUSR1 ; 
 int SIGUSR2 ; 
 int SIGWINCH ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recsig ; 
 int /*<<< orphan*/ * savsig ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pushsig(void)
{
#  ifndef OPENSSL_SYS_WIN32
    int i;
#  endif
#  ifdef SIGACTION
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = recsig;
#  endif

#  ifdef OPENSSL_SYS_WIN32
    savsig[SIGABRT] = signal(SIGABRT, recsig);
    savsig[SIGFPE] = signal(SIGFPE, recsig);
    savsig[SIGILL] = signal(SIGILL, recsig);
    savsig[SIGINT] = signal(SIGINT, recsig);
    savsig[SIGSEGV] = signal(SIGSEGV, recsig);
    savsig[SIGTERM] = signal(SIGTERM, recsig);
#  else
    for (i = 1; i < NX509_SIG; i++) {
#   ifdef SIGUSR1
        if (i == SIGUSR1)
            continue;
#   endif
#   ifdef SIGUSR2
        if (i == SIGUSR2)
            continue;
#   endif
#   ifdef SIGKILL
        if (i == SIGKILL)       /* We can't make any action on that. */
            continue;
#   endif
#   ifdef SIGACTION
        sigaction(i, &sa, &savsig[i]);
#   else
        savsig[i] = signal(i, recsig);
#   endif
    }
#  endif

#  ifdef SIGWINCH
    signal(SIGWINCH, SIG_DFL);
#  endif
}