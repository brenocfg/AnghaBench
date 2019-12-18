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
struct sigaction {scalar_t__ sa_handler; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  scalar_t__ pqsigfunc ;

/* Variables and functions */
 int /*<<< orphan*/  BlockSig ; 
 int /*<<< orphan*/  SA_NOCLDSTOP ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int SIGCHLD ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_ERR ; 
 scalar_t__ SIG_IGN ; 
 scalar_t__ pqsignal (int,scalar_t__) ; 
 scalar_t__ sigaction (int,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

pqsigfunc
pqsignal_pm(int signo, pqsigfunc func)
{
#ifndef WIN32
	struct sigaction act,
				oact;

	act.sa_handler = func;
	if (func == SIG_IGN || func == SIG_DFL)
	{
		/* in these cases, act the same as pqsignal() */
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_RESTART;
	}
	else
	{
		act.sa_mask = BlockSig;
		act.sa_flags = 0;
	}
#ifdef SA_NOCLDSTOP
	if (signo == SIGCHLD)
		act.sa_flags |= SA_NOCLDSTOP;
#endif
	if (sigaction(signo, &act, &oact) < 0)
		return SIG_ERR;
	return oact.sa_handler;
#else							/* WIN32 */
	return pqsignal(signo, func);
#endif
}