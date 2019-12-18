#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* slot; } ;
struct TYPE_8__ {int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {scalar_t__ bgw_notify_pid; } ;
struct TYPE_7__ {size_t rw_shmem_slot; TYPE_1__ rw_worker; int /*<<< orphan*/  rw_pid; } ;
typedef  TYPE_2__ RegisteredBgWorker ;
typedef  TYPE_3__ BackgroundWorkerSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_5__* BackgroundWorkerData ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t max_worker_processes ; 

void
ReportBackgroundWorkerPID(RegisteredBgWorker *rw)
{
	BackgroundWorkerSlot *slot;

	Assert(rw->rw_shmem_slot < max_worker_processes);
	slot = &BackgroundWorkerData->slot[rw->rw_shmem_slot];
	slot->pid = rw->rw_pid;

	if (rw->rw_worker.bgw_notify_pid != 0)
		kill(rw->rw_worker.bgw_notify_pid, SIGUSR1);
}