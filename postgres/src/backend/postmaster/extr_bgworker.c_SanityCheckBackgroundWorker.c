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
struct TYPE_3__ {int bgw_flags; scalar_t__ bgw_start_time; int bgw_restart_time; int /*<<< orphan*/  bgw_name; int /*<<< orphan*/  bgw_type; } ;
typedef  TYPE_1__ BackgroundWorker ;

/* Variables and functions */
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_CLASS_PARALLEL ; 
 int BGWORKER_SHMEM_ACCESS ; 
 int BGW_NEVER_RESTART ; 
 scalar_t__ BgWorkerStart_PostmasterStart ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int USECS_PER_DAY ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
SanityCheckBackgroundWorker(BackgroundWorker *worker, int elevel)
{
	/* sanity check for flags */
	if (worker->bgw_flags & BGWORKER_BACKEND_DATABASE_CONNECTION)
	{
		if (!(worker->bgw_flags & BGWORKER_SHMEM_ACCESS))
		{
			ereport(elevel,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("background worker \"%s\": must attach to shared memory in order to request a database connection",
							worker->bgw_name)));
			return false;
		}

		if (worker->bgw_start_time == BgWorkerStart_PostmasterStart)
		{
			ereport(elevel,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("background worker \"%s\": cannot request database access if starting at postmaster start",
							worker->bgw_name)));
			return false;
		}

		/* XXX other checks? */
	}

	if ((worker->bgw_restart_time < 0 &&
		 worker->bgw_restart_time != BGW_NEVER_RESTART) ||
		(worker->bgw_restart_time > USECS_PER_DAY / 1000))
	{
		ereport(elevel,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("background worker \"%s\": invalid restart interval",
						worker->bgw_name)));
		return false;
	}

	/*
	 * Parallel workers may not be configured for restart, because the
	 * parallel_register_count/parallel_terminate_count accounting can't
	 * handle parallel workers lasting through a crash-and-restart cycle.
	 */
	if (worker->bgw_restart_time != BGW_NEVER_RESTART &&
		(worker->bgw_flags & BGWORKER_CLASS_PARALLEL) != 0)
	{
		ereport(elevel,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("background worker \"%s\": parallel workers may not be configured for restart",
						worker->bgw_name)));
		return false;
	}

	/*
	 * If bgw_type is not filled in, use bgw_name.
	 */
	if (strcmp(worker->bgw_type, "") == 0)
		strcpy(worker->bgw_type, worker->bgw_name);

	return true;
}