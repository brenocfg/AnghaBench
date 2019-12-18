#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_6__ {int /*<<< orphan*/  workerStatus; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ ** te; TYPE_2__* parallelSlot; } ;
typedef  TYPE_1__ ParallelState ;
typedef  TYPE_2__ ParallelSlot ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  WRKR_IDLE ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getMessageFromWorker (TYPE_1__*,int,int*) ; 
 scalar_t__ messageStartsWith (char*,char*) ; 
 int parseWorkerResponse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ListenToWorkers(ArchiveHandle *AH, ParallelState *pstate, bool do_wait)
{
	int			worker;
	char	   *msg;

	/* Try to collect a status message */
	msg = getMessageFromWorker(pstate, do_wait, &worker);

	if (!msg)
	{
		/* If do_wait is true, we must have detected EOF on some socket */
		if (do_wait)
			fatal("a worker process died unexpectedly");
		return false;
	}

	/* Process it and update our idea of the worker's status */
	if (messageStartsWith(msg, "OK "))
	{
		ParallelSlot *slot = &pstate->parallelSlot[worker];
		TocEntry   *te = pstate->te[worker];
		int			status;

		status = parseWorkerResponse(AH, te, msg);
		slot->callback(AH, te, status, slot->callback_data);
		slot->workerStatus = WRKR_IDLE;
		pstate->te[worker] = NULL;
	}
	else
		fatal("invalid message received from worker: \"%s\"",
			  msg);

	/* Free the string returned from getMessageFromWorker */
	free(msg);

	return true;
}