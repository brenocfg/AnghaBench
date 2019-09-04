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
struct sigaction {scalar_t__ sa_restorer; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; scalar_t__ sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIGINFO ; 
 int SIGSEGV ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  handler ; 
 int sigaction (int,struct sigaction*,struct sigaction*) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void setup_handler()
{
	int r, rs;
	struct sigaction newact;
	struct sigaction oldact;

	/* #BR is mapped to sigsegv */
	int signum  = SIGSEGV;

	newact.sa_handler = 0;   /* void(*)(int)*/
	newact.sa_sigaction = handler; /* void (*)(int, siginfo_t*, void *) */

	/*sigset_t - signals to block while in the handler */
	/* get the old signal mask. */
	rs = sigprocmask(SIG_SETMASK, 0, &newact.sa_mask);
	assert(rs == 0);

	/* call sa_sigaction, not sa_handler*/
	newact.sa_flags = SA_SIGINFO;

	newact.sa_restorer = 0;  /* void(*)(), obsolete */
	r = sigaction(signum, &newact, &oldact);
	assert(r == 0);
}