#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_10__ {scalar_t__ pid; int /*<<< orphan*/  elem; } ;
struct TYPE_9__ {int /*<<< orphan*/  bgw_name; } ;
struct TYPE_8__ {scalar_t__ rw_pid; TYPE_3__* rw_backend; TYPE_2__ rw_worker; void* rw_crashed_at; int /*<<< orphan*/  rw_child_slot; int /*<<< orphan*/  rw_shmem_slot; } ;
typedef  TYPE_1__ RegisteredBgWorker ;
typedef  int /*<<< orphan*/  BackgroundWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BackendList ; 
 int /*<<< orphan*/  ClosePostmasterPorts (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 void* GetCurrentTimestamp () ; 
 int /*<<< orphan*/  InitPostmasterChild () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MyBgworkerEntry ; 
 int /*<<< orphan*/ * PostmasterContext ; 
 int /*<<< orphan*/  ReleasePostmasterChildSlot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportBackgroundWorkerPID (TYPE_1__*) ; 
 int /*<<< orphan*/  ShmemBackendArrayAdd (TYPE_3__*) ; 
 int /*<<< orphan*/  StartBackgroundWorker () ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  assign_backendlist_entry (TYPE_1__*) ; 
 scalar_t__ bgworker_forkexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork_process () ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static bool
do_start_bgworker(RegisteredBgWorker *rw)
{
	pid_t		worker_pid;

	Assert(rw->rw_pid == 0);

	/*
	 * Allocate and assign the Backend element.  Note we must do this before
	 * forking, so that we can handle failures (out of memory or child-process
	 * slots) cleanly.
	 *
	 * Treat failure as though the worker had crashed.  That way, the
	 * postmaster will wait a bit before attempting to start it again; if we
	 * tried again right away, most likely we'd find ourselves hitting the
	 * same resource-exhaustion condition.
	 */
	if (!assign_backendlist_entry(rw))
	{
		rw->rw_crashed_at = GetCurrentTimestamp();
		return false;
	}

	ereport(DEBUG1,
			(errmsg("starting background worker process \"%s\"",
					rw->rw_worker.bgw_name)));

#ifdef EXEC_BACKEND
	switch ((worker_pid = bgworker_forkexec(rw->rw_shmem_slot)))
#else
	switch ((worker_pid = fork_process()))
#endif
	{
		case -1:
			/* in postmaster, fork failed ... */
			ereport(LOG,
					(errmsg("could not fork worker process: %m")));
			/* undo what assign_backendlist_entry did */
			ReleasePostmasterChildSlot(rw->rw_child_slot);
			rw->rw_child_slot = 0;
			free(rw->rw_backend);
			rw->rw_backend = NULL;
			/* mark entry as crashed, so we'll try again later */
			rw->rw_crashed_at = GetCurrentTimestamp();
			break;

#ifndef EXEC_BACKEND
		case 0:
			/* in postmaster child ... */
			InitPostmasterChild();

			/* Close the postmaster's sockets */
			ClosePostmasterPorts(false);

			/*
			 * Before blowing away PostmasterContext, save this bgworker's
			 * data where it can find it.
			 */
			MyBgworkerEntry = (BackgroundWorker *)
				MemoryContextAlloc(TopMemoryContext, sizeof(BackgroundWorker));
			memcpy(MyBgworkerEntry, &rw->rw_worker, sizeof(BackgroundWorker));

			/* Release postmaster's working memory context */
			MemoryContextSwitchTo(TopMemoryContext);
			MemoryContextDelete(PostmasterContext);
			PostmasterContext = NULL;

			StartBackgroundWorker();

			exit(1);			/* should not get here */
			break;
#endif
		default:
			/* in postmaster, fork successful ... */
			rw->rw_pid = worker_pid;
			rw->rw_backend->pid = rw->rw_pid;
			ReportBackgroundWorkerPID(rw);
			/* add new worker to lists of backends */
			dlist_push_head(&BackendList, &rw->rw_backend->elem);
#ifdef EXEC_BACKEND
			ShmemBackendArrayAdd(rw->rw_backend);
#endif
			return true;
	}

	return false;
}