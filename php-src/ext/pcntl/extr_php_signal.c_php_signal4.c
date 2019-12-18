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
struct sigaction {int /*<<< orphan*/ * sa_handler; int /*<<< orphan*/ * sa_sigaction; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  int /*<<< orphan*/  Sigfunc ;

/* Variables and functions */
 int /*<<< orphan*/  SA_INTERRUPT ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_sigaction (int,struct sigaction*,struct sigaction*) ; 

Sigfunc *php_signal4(int signo, Sigfunc *func, int restart, int mask_all)
{
	struct sigaction act,oact;

#ifdef HAVE_STRUCT_SIGINFO_T
	act.sa_sigaction = func;
#else
	act.sa_handler = func;
#endif
	if (mask_all) {
		sigfillset(&act.sa_mask);
	} else {
		sigemptyset(&act.sa_mask);
	}
	act.sa_flags = 0;
#ifdef HAVE_STRUCT_SIGINFO_T
	act.sa_flags |= SA_SIGINFO;
#endif
	if (!restart) {
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT; /* SunOS */
#endif
	} else {
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART; /* SVR4, 4.3+BSD */
#endif
	}
	if (zend_sigaction(signo, &act, &oact) < 0) {
		return (Sigfunc*)SIG_ERR;
	}

#ifdef HAVE_STRUCT_SIGINFO_T
	return oact.sa_sigaction;
#else
	return oact.sa_handler;
#endif
}