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
typedef  int /*<<< orphan*/  CAC_state ;

/* Variables and functions */
 int /*<<< orphan*/  BACKEND_TYPE_ALL ; 
 int BACKEND_TYPE_BGWORKER ; 
 int /*<<< orphan*/  CAC_OK ; 
 int /*<<< orphan*/  CAC_RECOVERY ; 
 int /*<<< orphan*/  CAC_SHUTDOWN ; 
 int /*<<< orphan*/  CAC_STARTUP ; 
 int /*<<< orphan*/  CAC_TOOMANY ; 
 int /*<<< orphan*/  CAC_WAITBACKUP ; 
 scalar_t__ CountChildren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FatalError ; 
 scalar_t__ MaxLivePostmasterChildren () ; 
 scalar_t__ NoShutdown ; 
 scalar_t__ PM_HOT_STANDBY ; 
 scalar_t__ PM_RECOVERY ; 
 scalar_t__ PM_RUN ; 
 scalar_t__ PM_STARTUP ; 
 scalar_t__ PM_WAIT_BACKUP ; 
 scalar_t__ Shutdown ; 
 scalar_t__ pmState ; 

__attribute__((used)) static CAC_state
canAcceptConnections(int backend_type)
{
	CAC_state	result = CAC_OK;

	/*
	 * Can't start backends when in startup/shutdown/inconsistent recovery
	 * state.  We treat autovac workers the same as user backends for this
	 * purpose.  However, bgworkers are excluded from this test; we expect
	 * bgworker_should_start_now() decided whether the DB state allows them.
	 *
	 * In state PM_WAIT_BACKUP only superusers can connect (this must be
	 * allowed so that a superuser can end online backup mode); we return
	 * CAC_WAITBACKUP code to indicate that this must be checked later. Note
	 * that neither CAC_OK nor CAC_WAITBACKUP can safely be returned until we
	 * have checked for too many children.
	 */
	if (pmState != PM_RUN &&
		backend_type != BACKEND_TYPE_BGWORKER)
	{
		if (pmState == PM_WAIT_BACKUP)
			result = CAC_WAITBACKUP;	/* allow superusers only */
		else if (Shutdown > NoShutdown)
			return CAC_SHUTDOWN;	/* shutdown is pending */
		else if (!FatalError &&
				 (pmState == PM_STARTUP ||
				  pmState == PM_RECOVERY))
			return CAC_STARTUP; /* normal startup */
		else if (!FatalError &&
				 pmState == PM_HOT_STANDBY)
			result = CAC_OK;	/* connection OK during hot standby */
		else
			return CAC_RECOVERY;	/* else must be crash recovery */
	}

	/*
	 * Don't start too many children.
	 *
	 * We allow more connections here than we can have backends because some
	 * might still be authenticating; they might fail auth, or some existing
	 * backend might exit before the auth cycle is completed.  The exact
	 * MaxBackends limit is enforced when a new backend tries to join the
	 * shared-inval backend array.
	 *
	 * The limit here must match the sizes of the per-child-process arrays;
	 * see comments for MaxLivePostmasterChildren().
	 */
	if (CountChildren(BACKEND_TYPE_ALL) >= MaxLivePostmasterChildren())
		result = CAC_TOOMANY;

	return result;
}