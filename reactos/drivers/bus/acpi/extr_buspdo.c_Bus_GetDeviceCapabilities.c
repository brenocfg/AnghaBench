#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ Status; } ;
struct TYPE_16__ {TYPE_5__* Capabilities; } ;
struct TYPE_17__ {TYPE_2__ DeviceCapabilities; } ;
struct TYPE_19__ {int Size; int Version; int Address; int UINumber; TYPE_3__ Parameters; int /*<<< orphan*/  MinorFunction; int /*<<< orphan*/  MajorFunction; } ;
struct TYPE_15__ {int /*<<< orphan*/  Status; } ;
struct TYPE_18__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  TYPE_5__* PDEVICE_CAPABILITIES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  TYPE_7__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  IO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  DEVICE_CAPABILITIES ;

/* Variables and functions */
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRP_MJ_PNP ; 
 int /*<<< orphan*/  IRP_MN_QUERY_CAPABILITIES ; 
 TYPE_4__* IoBuildSynchronousFsdRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IoGetAttachedDeviceReference (int /*<<< orphan*/ ) ; 
 TYPE_5__* IoGetNextIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_5__*,int) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 
 scalar_t__ STATUS_PENDING ; 

NTSTATUS
Bus_GetDeviceCapabilities(
      PDEVICE_OBJECT          DeviceObject,
      PDEVICE_CAPABILITIES    DeviceCapabilities
    )
{
    IO_STATUS_BLOCK     ioStatus;
    KEVENT              pnpEvent;
    NTSTATUS            status;
    PDEVICE_OBJECT      targetObject;
    PIO_STACK_LOCATION  irpStack;
    PIRP                pnpIrp;

    PAGED_CODE();

    //
    // Initialize the capabilities that we will send down
    //
    RtlZeroMemory( DeviceCapabilities, sizeof(DEVICE_CAPABILITIES) );
    DeviceCapabilities->Size = sizeof(DEVICE_CAPABILITIES);
    DeviceCapabilities->Version = 1;
    DeviceCapabilities->Address = -1;
    DeviceCapabilities->UINumber = -1;

    //
    // Initialize the event
    //
    KeInitializeEvent( &pnpEvent, NotificationEvent, FALSE );

    targetObject = IoGetAttachedDeviceReference( DeviceObject );

    //
    // Build an Irp
    //
    pnpIrp = IoBuildSynchronousFsdRequest(
        IRP_MJ_PNP,
        targetObject,
        NULL,
        0,
        NULL,
        &pnpEvent,
        &ioStatus
        );
    if (pnpIrp == NULL) {

        status = STATUS_INSUFFICIENT_RESOURCES;
        goto GetDeviceCapabilitiesExit;

    }

    //
    // Pnp Irps all begin life as STATUS_NOT_SUPPORTED;
    //
    pnpIrp->IoStatus.Status = STATUS_NOT_SUPPORTED;

    //
    // Get the top of stack
    //
    irpStack = IoGetNextIrpStackLocation( pnpIrp );

    //
    // Set the top of stack
    //
    RtlZeroMemory( irpStack, sizeof(IO_STACK_LOCATION ) );
    irpStack->MajorFunction = IRP_MJ_PNP;
    irpStack->MinorFunction = IRP_MN_QUERY_CAPABILITIES;
    irpStack->Parameters.DeviceCapabilities.Capabilities = DeviceCapabilities;

    //
    // Call the driver
    //
    status = IoCallDriver( targetObject, pnpIrp );
    if (status == STATUS_PENDING) {

        //
        // Block until the irp comes back.
        // Important thing to note here is when you allocate
        // the memory for an event in the stack you must do a
        // KernelMode wait instead of UserMode to prevent
        // the stack from getting paged out.
        //

        KeWaitForSingleObject(
            &pnpEvent,
            Executive,
            KernelMode,
            FALSE,
            NULL
            );
        status = ioStatus.Status;

    }

GetDeviceCapabilitiesExit:
    //
    // Done with reference
    //
    ObDereferenceObject( targetObject );

    //
    // Done
    //
    return status;

}