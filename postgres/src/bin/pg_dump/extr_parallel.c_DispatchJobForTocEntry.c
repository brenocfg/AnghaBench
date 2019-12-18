#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  TocEntry ;
typedef  int /*<<< orphan*/  T_Action ;
struct TYPE_8__ {int /*<<< orphan*/ ** te; TYPE_1__* parallelSlot; } ;
struct TYPE_7__ {void* callback_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  workerStatus; } ;
typedef  TYPE_2__ ParallelState ;
typedef  int /*<<< orphan*/  ParallelCompletionPtr ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int GetIdleWorker (TYPE_2__*) ; 
 int NO_SLOT ; 
 int /*<<< orphan*/  WFW_ONE_IDLE ; 
 int /*<<< orphan*/  WRKR_WORKING ; 
 int /*<<< orphan*/  WaitForWorkers (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buildWorkerCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sendMessageToWorker (TYPE_2__*,int,char*) ; 

void
DispatchJobForTocEntry(ArchiveHandle *AH,
					   ParallelState *pstate,
					   TocEntry *te,
					   T_Action act,
					   ParallelCompletionPtr callback,
					   void *callback_data)
{
	int			worker;
	char		buf[256];

	/* Get a worker, waiting if none are idle */
	while ((worker = GetIdleWorker(pstate)) == NO_SLOT)
		WaitForWorkers(AH, pstate, WFW_ONE_IDLE);

	/* Construct and send command string */
	buildWorkerCommand(AH, te, act, buf, sizeof(buf));

	sendMessageToWorker(pstate, worker, buf);

	/* Remember worker is busy, and which TocEntry it's working on */
	pstate->parallelSlot[worker].workerStatus = WRKR_WORKING;
	pstate->parallelSlot[worker].callback = callback;
	pstate->parallelSlot[worker].callback_data = callback_data;
	pstate->te[worker] = te;
}