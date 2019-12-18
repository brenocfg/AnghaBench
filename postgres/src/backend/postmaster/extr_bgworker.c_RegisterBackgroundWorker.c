#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bgw_notify_pid; int /*<<< orphan*/  bgw_name; int /*<<< orphan*/  bgw_library_name; } ;
struct TYPE_6__ {int rw_terminate; int /*<<< orphan*/  rw_lnode; scalar_t__ rw_crashed_at; scalar_t__ rw_child_slot; scalar_t__ rw_pid; int /*<<< orphan*/ * rw_backend; TYPE_2__ rw_worker; } ;
typedef  TYPE_1__ RegisteredBgWorker ;
typedef  TYPE_2__ BackgroundWorker ;

/* Variables and functions */
 int /*<<< orphan*/  BackgroundWorkerList ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERRCODE_CONFIGURATION_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  SanityCheckBackgroundWorker (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_plural (char*,char*,int,int) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_1__* malloc (int) ; 
 int max_worker_processes ; 
 int /*<<< orphan*/  process_shared_preload_libraries_in_progress ; 
 int /*<<< orphan*/  slist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
RegisterBackgroundWorker(BackgroundWorker *worker)
{
	RegisteredBgWorker *rw;
	static int	numworkers = 0;

	if (!IsUnderPostmaster)
		ereport(DEBUG1,
				(errmsg("registering background worker \"%s\"", worker->bgw_name)));

	if (!process_shared_preload_libraries_in_progress &&
		strcmp(worker->bgw_library_name, "postgres") != 0)
	{
		if (!IsUnderPostmaster)
			ereport(LOG,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("background worker \"%s\": must be registered in shared_preload_libraries",
							worker->bgw_name)));
		return;
	}

	if (!SanityCheckBackgroundWorker(worker, LOG))
		return;

	if (worker->bgw_notify_pid != 0)
	{
		ereport(LOG,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("background worker \"%s\": only dynamic background workers can request notification",
						worker->bgw_name)));
		return;
	}

	/*
	 * Enforce maximum number of workers.  Note this is overly restrictive: we
	 * could allow more non-shmem-connected workers, because these don't count
	 * towards the MAX_BACKENDS limit elsewhere.  For now, it doesn't seem
	 * important to relax this restriction.
	 */
	if (++numworkers > max_worker_processes)
	{
		ereport(LOG,
				(errcode(ERRCODE_CONFIGURATION_LIMIT_EXCEEDED),
				 errmsg("too many background workers"),
				 errdetail_plural("Up to %d background worker can be registered with the current settings.",
								  "Up to %d background workers can be registered with the current settings.",
								  max_worker_processes,
								  max_worker_processes),
				 errhint("Consider increasing the configuration parameter \"max_worker_processes\".")));
		return;
	}

	/*
	 * Copy the registration data into the registered workers list.
	 */
	rw = malloc(sizeof(RegisteredBgWorker));
	if (rw == NULL)
	{
		ereport(LOG,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));
		return;
	}

	rw->rw_worker = *worker;
	rw->rw_backend = NULL;
	rw->rw_pid = 0;
	rw->rw_child_slot = 0;
	rw->rw_crashed_at = 0;
	rw->rw_terminate = false;

	slist_push_head(&BackgroundWorkerList, &rw->rw_lnode);
}