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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  Information; int /*<<< orphan*/  Status; } ;
struct TYPE_7__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_2__* PVOID ;
typedef  TYPE_2__* PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IRP ; 
 int /*<<< orphan*/  IRPFinish (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID DispDataRequestComplete(
    PVOID Context,
    NTSTATUS Status,
    ULONG Count)
/*
 * FUNCTION: Completes a send/receive IRP
 * ARGUMENTS:
 *     Context = Pointer to context information (IRP)
 *     Status  = Status of the request
 *     Count   = Number of bytes sent or received
 */
{
    PIRP Irp = Context;

    TI_DbgPrint(DEBUG_IRP, ("Called for irp %x (%x, %d).\n",
			    Irp, Status, Count));

    Irp->IoStatus.Status      = Status;
    Irp->IoStatus.Information = Count;

    TI_DbgPrint(MID_TRACE, ("Irp->IoStatus.Status = %x\n",
			    Irp->IoStatus.Status));
    TI_DbgPrint(MID_TRACE, ("Irp->IoStatus.Information = %d\n",
			    Irp->IoStatus.Information));
    TI_DbgPrint(DEBUG_IRP, ("Completing IRP at (0x%X).\n", Irp));

    IRPFinish(Irp, Status);

    TI_DbgPrint(DEBUG_IRP, ("Done Completing IRP\n"));
}