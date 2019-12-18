#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ Status; scalar_t__ Information; } ;
struct TYPE_14__ {int /*<<< orphan*/  IdType; } ;
struct TYPE_15__ {TYPE_2__ QueryId; } ;
struct TYPE_17__ {TYPE_3__ Parameters; int /*<<< orphan*/  MinorFunction; int /*<<< orphan*/  MajorFunction; } ;
struct TYPE_13__ {int /*<<< orphan*/  Status; } ;
struct TYPE_16__ {TYPE_1__ IoStatus; } ;
typedef  scalar_t__ PWSTR ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  TYPE_6__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  IO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  BUS_QUERY_ID_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRP_MJ_PNP ; 
 int /*<<< orphan*/  IRP_MN_QUERY_ID ; 
 TYPE_4__* IoBuildSynchronousFsdRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IoGetAttachedDeviceReference (int /*<<< orphan*/ ) ; 
 TYPE_5__* IoGetNextIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_5__*,int) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 
 scalar_t__ STATUS_PENDING ; 

__attribute__((used)) static
NTSTATUS
GetDeviceId(
    PDEVICE_OBJECT DeviceObject,
    BUS_QUERY_ID_TYPE IdType,
    PWSTR *DeviceId)
{
    PIO_STACK_LOCATION IrpStack;
    IO_STATUS_BLOCK IoStatus;
    PDEVICE_OBJECT TargetObject;
    KEVENT Event;
    PIRP Irp;
    NTSTATUS Status;

    PAGED_CODE();

    /* Initialize the event */
    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    TargetObject = IoGetAttachedDeviceReference(DeviceObject);

    /* Build the IRP */
    Irp = IoBuildSynchronousFsdRequest(IRP_MJ_PNP,
                                       TargetObject,
                                       NULL,
                                       0,
                                       NULL,
                                       &Event,
                                       &IoStatus);
    if (Irp == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    /* PNP IRPs all begin life as STATUS_NOT_SUPPORTED */
    Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;

    /* Get the top of stack */
    IrpStack = IoGetNextIrpStackLocation(Irp);

    /* Set the top of stack */
    RtlZeroMemory(IrpStack, sizeof(IO_STACK_LOCATION));
    IrpStack->MajorFunction = IRP_MJ_PNP;
    IrpStack->MinorFunction = IRP_MN_QUERY_ID;
    IrpStack->Parameters.QueryId.IdType = IdType;

    /* Call the driver */
    Status = IoCallDriver(TargetObject, Irp);
    if (Status == STATUS_PENDING)
    {
        KeWaitForSingleObject(&Event,
                              Executive,
                              KernelMode,
                              FALSE,
                              NULL);

        Status = IoStatus.Status;
    }

    if (NT_SUCCESS(Status))
    {
        *DeviceId = (PWSTR)IoStatus.Information;
    }

done:
    /* Dereference the target device object */
    ObDereferenceObject(TargetObject);

    return Status;
}