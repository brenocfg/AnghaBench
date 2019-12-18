#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int MinorFunction; int Flags; TYPE_2__* Irp; } ;
struct TYPE_7__ {scalar_t__ Information; } ;
struct TYPE_8__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_3__* PNTFS_IRP_CONTEXT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int IRPCONTEXT_COMPLETE ; 
#define  IRP_MN_NOTIFY_CHANGE_DIRECTORY 129 
#define  IRP_MN_QUERY_DIRECTORY 128 
 scalar_t__ NtfsMarkIrpContextForQueue (TYPE_3__*) ; 
 scalar_t__ NtfsQueryDirectory (TYPE_3__*) ; 
 scalar_t__ STATUS_INVALID_DEVICE_REQUEST ; 
 scalar_t__ STATUS_NOT_IMPLEMENTED ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_UNSUCCESSFUL ; 

NTSTATUS
NtfsDirectoryControl(PNTFS_IRP_CONTEXT IrpContext)
{
    NTSTATUS Status = STATUS_UNSUCCESSFUL;

    DPRINT("NtfsDirectoryControl() called\n");

    switch (IrpContext->MinorFunction)
    {
        case IRP_MN_QUERY_DIRECTORY:
            Status = NtfsQueryDirectory(IrpContext);
            break;

        case IRP_MN_NOTIFY_CHANGE_DIRECTORY:
            DPRINT1("IRP_MN_NOTIFY_CHANGE_DIRECTORY\n");
            Status = STATUS_NOT_IMPLEMENTED;
            break;

        default:
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    if (Status == STATUS_PENDING && IrpContext->Flags & IRPCONTEXT_COMPLETE)
    {
        return NtfsMarkIrpContextForQueue(IrpContext);
    }

    IrpContext->Irp->IoStatus.Information = 0;

    return Status;
}