#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Flags; int /*<<< orphan*/  WorkQueueItem; int /*<<< orphan*/  Irp; } ;
typedef  TYPE_1__* PNTFS_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CriticalWorkQueue ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExInitializeWorkItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ExQueueWorkItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRPCONTEXT_CANWAIT ; 
 int IRPCONTEXT_COMPLETE ; 
 int IRPCONTEXT_QUEUE ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoMarkIrpPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsDoRequest ; 
 int /*<<< orphan*/  QueueCount ; 
 int /*<<< orphan*/  STATUS_PENDING ; 

__attribute__((used)) static
NTSTATUS
NtfsQueueRequest(PNTFS_IRP_CONTEXT IrpContext)
{
    InterlockedIncrement(&QueueCount);
    DPRINT("NtfsQueueRequest(IrpContext %p), %d\n", IrpContext, QueueCount);

    ASSERT(!(IrpContext->Flags & IRPCONTEXT_QUEUE) &&
           (IrpContext->Flags & IRPCONTEXT_COMPLETE));
    IrpContext->Flags |= IRPCONTEXT_CANWAIT;
    IoMarkIrpPending(IrpContext->Irp);
    ExInitializeWorkItem(&IrpContext->WorkQueueItem, NtfsDoRequest, IrpContext);
    ExQueueWorkItem(&IrpContext->WorkQueueItem, CriticalWorkQueue);

    return STATUS_PENDING;
}