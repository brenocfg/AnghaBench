#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_21__ {int Count; int /*<<< orphan*/ * Objects; } ;
struct TYPE_14__ {int Type; } ;
struct TYPE_15__ {TYPE_1__ QueryDeviceRelations; } ;
struct TYPE_20__ {TYPE_2__ Parameters; } ;
struct TYPE_17__ {int /*<<< orphan*/  Status; int /*<<< orphan*/  Information; } ;
struct TYPE_19__ {TYPE_4__ IoStatus; } ;
struct TYPE_16__ {int /*<<< orphan*/  Self; } ;
struct TYPE_18__ {TYPE_3__ Common; } ;
typedef  TYPE_5__* PPDO_DEVICE_DATA ;
typedef  TYPE_6__* PIRP ;
typedef  TYPE_7__* PIO_STACK_LOCATION ;
typedef  TYPE_8__* PDEVICE_RELATIONS ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DEVICE_RELATIONS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERTMSG (char*,int) ; 
#define  BusRelations 131 
#define  EjectionRelations 130 
 TYPE_8__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 TYPE_7__* IoGetCurrentIrpStackLocation (TYPE_6__*) ; 
 int /*<<< orphan*/  ObReferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  PagedPool ; 
#define  RemovalRelations 129 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
#define  TargetDeviceRelation 128 

NTSTATUS
Bus_PDO_QueryDeviceRelations(
     PPDO_DEVICE_DATA     DeviceData,
      PIRP   Irp )
/*++

Routine Description:

    The PnP Manager sends this IRP to gather information about
    devices with a relationship to the specified device.
    Bus drivers must handle this request for TargetDeviceRelation
    for their child devices (child PDOs).

    If a driver returns relations in response to this IRP,
    it allocates a DEVICE_RELATIONS structure from paged
    memory containing a count and the appropriate number of
    device object pointers. The PnP Manager frees the structure
    when it is no longer needed. If a driver replaces a
    DEVICE_RELATIONS structure allocated by another driver,
    it must free the previous structure.

    A driver must reference the PDO of any device that it
    reports in this IRP (ObReferenceObject). The PnP Manager
    removes the reference when appropriate.

Arguments:

    DeviceData - Pointer to the PDO's device extension.
    Irp          - Pointer to the irp.

Return Value:

    NT STATUS

--*/
{

    PIO_STACK_LOCATION   stack;
    PDEVICE_RELATIONS deviceRelations;
    NTSTATUS status;

    PAGED_CODE ();

    stack = IoGetCurrentIrpStackLocation (Irp);

    switch (stack->Parameters.QueryDeviceRelations.Type) {

    case TargetDeviceRelation:

        deviceRelations = (PDEVICE_RELATIONS) Irp->IoStatus.Information;
        if (deviceRelations) {
            //
            // Only PDO can handle this request. Somebody above
            // is not playing by rule.
            //
            ASSERTMSG("Someone above is handling TargetDeviceRelation\n", !deviceRelations);
        }

        deviceRelations = ExAllocatePoolWithTag(PagedPool,
                                                sizeof(DEVICE_RELATIONS),
                                                'IpcA');
        if (!deviceRelations) {
                status = STATUS_INSUFFICIENT_RESOURCES;
                break;
        }

        //
        // There is only one PDO pointer in the structure
        // for this relation type. The PnP Manager removes
        // the reference to the PDO when the driver or application
        // un-registers for notification on the device.
        //

        deviceRelations->Count = 1;
        deviceRelations->Objects[0] = DeviceData->Common.Self;
        ObReferenceObject(DeviceData->Common.Self);

        status = STATUS_SUCCESS;
        Irp->IoStatus.Information = (ULONG_PTR) deviceRelations;
        break;

    case BusRelations: // Not handled by PDO
    case EjectionRelations: // optional for PDO
    case RemovalRelations: // // optional for PDO
    default:
        status = Irp->IoStatus.Status;
    }

    return status;
}