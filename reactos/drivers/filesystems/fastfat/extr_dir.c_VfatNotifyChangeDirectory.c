#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  CompletionFilter; } ;
struct TYPE_11__ {TYPE_2__ NotifyDirectory; } ;
struct TYPE_15__ {TYPE_3__ Parameters; int /*<<< orphan*/  Flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  NotifyList; int /*<<< orphan*/  NotifySync; } ;
struct TYPE_13__ {int /*<<< orphan*/  PathNameU; } ;
struct TYPE_12__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Irp; TYPE_1__* FileObject; TYPE_6__* DeviceExt; TYPE_7__* Stack; } ;
struct TYPE_9__ {int /*<<< orphan*/  FsContext2; scalar_t__ FsContext; } ;
typedef  TYPE_4__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_5__* PVFATFCB ;
typedef  TYPE_6__* PVCB ;
typedef  int /*<<< orphan*/  PSTRING ;
typedef  TYPE_7__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FsRtlNotifyFullChangeDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRPCONTEXT_COMPLETE ; 
 int /*<<< orphan*/  SL_WATCH_TREE ; 
 int /*<<< orphan*/  STATUS_PENDING ; 

NTSTATUS VfatNotifyChangeDirectory(PVFAT_IRP_CONTEXT IrpContext)
{
    PVCB pVcb;
    PVFATFCB pFcb;
    PIO_STACK_LOCATION Stack;
    Stack = IrpContext->Stack;
    pVcb = IrpContext->DeviceExt;
    pFcb = (PVFATFCB) IrpContext->FileObject->FsContext;

    FsRtlNotifyFullChangeDirectory(pVcb->NotifySync,
                                   &(pVcb->NotifyList),
                                   IrpContext->FileObject->FsContext2,
                                   (PSTRING)&(pFcb->PathNameU),
                                   BooleanFlagOn(Stack->Flags, SL_WATCH_TREE),
                                   FALSE,
                                   Stack->Parameters.NotifyDirectory.CompletionFilter,
                                   IrpContext->Irp,
                                   NULL,
                                   NULL);

    /* We won't handle IRP completion */
    IrpContext->Flags &= ~IRPCONTEXT_COMPLETE;

    return STATUS_PENDING;
}