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
struct TYPE_7__ {scalar_t__ Status; } ;
struct TYPE_6__ {int /*<<< orphan*/  UserEvent; } ;
typedef  int /*<<< orphan*/ * PKEVENT ;
typedef  TYPE_1__* PIRP ;
typedef  TYPE_2__* PIO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 scalar_t__ STATUS_PENDING ; 

__attribute__((used)) static NTSTATUS TdiCall(
    PIRP Irp,
    PDEVICE_OBJECT DeviceObject,
    PKEVENT Event,
    PIO_STATUS_BLOCK Iosb)
/*
 * FUNCTION: Calls a transport driver device
 * ARGUMENTS:
 *     Irp           = Pointer to I/O Request Packet
 *     DeviceObject  = Pointer to device object to call
 *     Event         = An optional pointer to an event handle that will be
 *                     waited upon
 *     Iosb          = Pointer to an IO status block
 * RETURNS:
 *     Status of operation
 */
{
    NTSTATUS Status;

    AFD_DbgPrint(MID_TRACE, ("Called\n"));

    AFD_DbgPrint(MID_TRACE, ("Irp->UserEvent = %p\n", Irp->UserEvent));

    Status = IoCallDriver(DeviceObject, Irp);
    AFD_DbgPrint(MID_TRACE, ("IoCallDriver: %08x\n", Status));

    if ((Status == STATUS_PENDING) && (Event != NULL)) {
        AFD_DbgPrint(MAX_TRACE, ("Waiting on transport.\n"));
        KeWaitForSingleObject(Event,
                              Executive,
                              KernelMode,
                              FALSE,
                              NULL);
        Status = Iosb->Status;
    }

    AFD_DbgPrint(MAX_TRACE, ("Status (0x%X).\n", Status));

    return Status;
}