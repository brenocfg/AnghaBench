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
 int /*<<< orphan*/  ERROR ; 
 int POSTMASTER_DEATH_SIGNAL ; 
 int /*<<< orphan*/  PROC_PDEATHSIG_CTL ; 
 int /*<<< orphan*/  PR_SET_PDEATHSIG ; 
 int /*<<< orphan*/  P_PID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  postmaster_death_handler ; 
 int postmaster_possibly_dead ; 
 int /*<<< orphan*/  pqsignal (int,int /*<<< orphan*/ ) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ procctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
PostmasterDeathSignalInit(void)
{
#ifdef USE_POSTMASTER_DEATH_SIGNAL
	int			signum = POSTMASTER_DEATH_SIGNAL;

	/* Register our signal handler. */
	pqsignal(signum, postmaster_death_handler);

	/* Request a signal on parent exit. */
#if defined(PR_SET_PDEATHSIG)
	if (prctl(PR_SET_PDEATHSIG, signum) < 0)
		elog(ERROR, "could not request parent death signal: %m");
#elif defined(PROC_PDEATHSIG_CTL)
	if (procctl(P_PID, 0, PROC_PDEATHSIG_CTL, &signum) < 0)
		elog(ERROR, "could not request parent death signal: %m");
#else
#error "USE_POSTMASTER_DEATH_SIGNAL set, but there is no mechanism to request the signal"
#endif

	/*
	 * Just in case the parent was gone already and we missed it, we'd better
	 * check the slow way on the first call.
	 */
	postmaster_possibly_dead = true;
#endif							/* USE_POSTMASTER_DEATH_SIGNAL */
}