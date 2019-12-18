#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nworkers; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ worker_state ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ BgwHandleStatus ;

/* Variables and functions */
 scalar_t__ BGWH_POSTMASTER_DIED ; 
 scalar_t__ BGWH_STOPPED ; 
 scalar_t__ GetBackgroundWorkerPid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
check_worker_status(worker_state *wstate)
{
	int			n;

	/* If any workers (or the postmaster) have died, we have failed. */
	for (n = 0; n < wstate->nworkers; ++n)
	{
		BgwHandleStatus status;
		pid_t		pid;

		status = GetBackgroundWorkerPid(wstate->handle[n], &pid);
		if (status == BGWH_STOPPED || status == BGWH_POSTMASTER_DIED)
			return false;
	}

	/* Otherwise, things still look OK. */
	return true;
}