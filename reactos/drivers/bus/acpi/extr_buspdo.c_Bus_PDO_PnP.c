#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_13__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
struct TYPE_38__ {int /*<<< orphan*/  hardware_id; } ;
struct TYPE_37__ {int /*<<< orphan*/  hardware_id; } ;
struct acpi_device {TYPE_2__ pnp; TYPE_1__ flags; } ;
struct TYPE_39__ {int /*<<< orphan*/  Type; } ;
struct TYPE_40__ {TYPE_3__ QueryDeviceRelations; } ;
struct TYPE_45__ {int MinorFunction; TYPE_4__ Parameters; } ;
struct TYPE_41__ {int /*<<< orphan*/  Status; } ;
struct TYPE_44__ {TYPE_5__ IoStatus; } ;
struct TYPE_43__ {void* DeviceState; } ;
struct TYPE_35__ {int /*<<< orphan*/  DevicePnPState; void* DevicePowerState; int /*<<< orphan*/  Self; } ;
struct TYPE_36__ {int /*<<< orphan*/  Length; } ;
struct TYPE_42__ {TYPE_10__ Common; scalar_t__ AcpiHandle; TYPE_13__ InterfaceName; } ;
typedef  TYPE_6__* PPDO_DEVICE_DATA ;
typedef  TYPE_7__ POWER_STATE ;
typedef  TYPE_8__* PIRP ;
typedef  TYPE_9__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUTTON_HID_LID ; 
 int /*<<< orphan*/  ACPI_PROCESSOR_HID ; 
 int /*<<< orphan*/  ACPI_STATE_D0 ; 
 int /*<<< orphan*/  ACPI_STATE_D3 ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_THERMAL_HID ; 
 int /*<<< orphan*/  Bus_PDO_QueryBusInformation (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryDeviceCaps (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryDeviceId (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryDeviceRelations (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryDeviceText (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryInterface (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryResourceRequirements (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Bus_PDO_QueryResources (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  DbgDeviceRelationString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DevicePowerState ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_DEVICE_LID ; 
 int /*<<< orphan*/  GUID_DEVICE_PROCESSOR ; 
 int /*<<< orphan*/  GUID_DEVICE_SYS_BUTTON ; 
 int /*<<< orphan*/  GUID_DEVICE_THERMAL_ZONE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
#define  IRP_MN_CANCEL_REMOVE_DEVICE 143 
#define  IRP_MN_CANCEL_STOP_DEVICE 142 
#define  IRP_MN_FILTER_RESOURCE_REQUIREMENTS 141 
#define  IRP_MN_QUERY_BUS_INFORMATION 140 
#define  IRP_MN_QUERY_CAPABILITIES 139 
#define  IRP_MN_QUERY_DEVICE_RELATIONS 138 
#define  IRP_MN_QUERY_DEVICE_TEXT 137 
#define  IRP_MN_QUERY_ID 136 
#define  IRP_MN_QUERY_INTERFACE 135 
#define  IRP_MN_QUERY_REMOVE_DEVICE 134 
#define  IRP_MN_QUERY_RESOURCES 133 
#define  IRP_MN_QUERY_RESOURCE_REQUIREMENTS 132 
#define  IRP_MN_QUERY_STOP_DEVICE 131 
#define  IRP_MN_REMOVE_DEVICE 130 
#define  IRP_MN_START_DEVICE 129 
#define  IRP_MN_STOP_DEVICE 128 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoRegisterDeviceInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_13__*) ; 
 int /*<<< orphan*/  IoSetDeviceInterfaceState (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  PoSetPowerState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__) ; 
 void* PowerDeviceD0 ; 
 void* PowerDeviceD3 ; 
 int /*<<< orphan*/  RESTORE_PREVIOUS_PNP_STATE (TYPE_10__) ; 
 int /*<<< orphan*/  RemovalPending ; 
 int /*<<< orphan*/  SET_NEW_PNP_STATE (TYPE_10__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  Started ; 
 int /*<<< orphan*/  StopPending ; 
 int /*<<< orphan*/  Stopped ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_bus_get_device (scalar_t__,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_bus_power_manageable (scalar_t__) ; 
 int /*<<< orphan*/  acpi_bus_set_power (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
Bus_PDO_PnP (
     PDEVICE_OBJECT       DeviceObject,
     PIRP                 Irp,
     PIO_STACK_LOCATION   IrpStack,
     PPDO_DEVICE_DATA     DeviceData
    )
{
    NTSTATUS                status;
    POWER_STATE             state;
    struct acpi_device      *device = NULL;

    PAGED_CODE ();

    if (DeviceData->AcpiHandle)
        acpi_bus_get_device(DeviceData->AcpiHandle, &device);

    //
    // NB: Because we are a bus enumerator, we have no one to whom we could
    // defer these irps.  Therefore we do not pass them down but merely
    // return them.
    //

    switch (IrpStack->MinorFunction) {

    case IRP_MN_START_DEVICE:
        //
        // Here we do what ever initialization and ``turning on'' that is
        // required to allow others to access this device.
        // Power up the device.
        //
        if (DeviceData->AcpiHandle && acpi_bus_power_manageable(DeviceData->AcpiHandle) &&
            !ACPI_SUCCESS(acpi_bus_set_power(DeviceData->AcpiHandle, ACPI_STATE_D0)))
        {
            DPRINT1("Device %x failed to start!\n", DeviceData->AcpiHandle);
            status = STATUS_UNSUCCESSFUL;
            break;
        }

        DeviceData->InterfaceName.Length = 0;
        status = STATUS_SUCCESS;

        if (!device)
        {
            status = IoRegisterDeviceInterface(DeviceData->Common.Self,
                                               &GUID_DEVICE_SYS_BUTTON,
                                               NULL,
                                               &DeviceData->InterfaceName);
        }
        else if (device->flags.hardware_id &&
                 strstr(device->pnp.hardware_id, ACPI_THERMAL_HID))
        {
            status = IoRegisterDeviceInterface(DeviceData->Common.Self,
                                               &GUID_DEVICE_THERMAL_ZONE,
                                               NULL,
                                               &DeviceData->InterfaceName);
        }
        else if (device->flags.hardware_id &&
                 strstr(device->pnp.hardware_id, ACPI_BUTTON_HID_LID))
        {
            status = IoRegisterDeviceInterface(DeviceData->Common.Self,
                                               &GUID_DEVICE_LID,
                                               NULL,
                                               &DeviceData->InterfaceName);
        }
        else if (device->flags.hardware_id &&
                 strstr(device->pnp.hardware_id, ACPI_PROCESSOR_HID))
        {
            status = IoRegisterDeviceInterface(DeviceData->Common.Self,
                                               &GUID_DEVICE_PROCESSOR,
                                               NULL,
                                               &DeviceData->InterfaceName);
        }

        /* Failure to register an interface is not a fatal failure so don't return a failure status */
        if (NT_SUCCESS(status) && DeviceData->InterfaceName.Length != 0)
            IoSetDeviceInterfaceState(&DeviceData->InterfaceName, TRUE);

        state.DeviceState = PowerDeviceD0;
        PoSetPowerState(DeviceData->Common.Self, DevicePowerState, state);
        DeviceData->Common.DevicePowerState = PowerDeviceD0;
        SET_NEW_PNP_STATE(DeviceData->Common, Started);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_STOP_DEVICE:

        if (DeviceData->InterfaceName.Length != 0)
            IoSetDeviceInterfaceState(&DeviceData->InterfaceName, FALSE);

        //
        // Here we shut down the device and give up and unmap any resources
        // we acquired for the device.
        //
        if (DeviceData->AcpiHandle && acpi_bus_power_manageable(DeviceData->AcpiHandle) &&
            !ACPI_SUCCESS(acpi_bus_set_power(DeviceData->AcpiHandle, ACPI_STATE_D3)))
        {
            DPRINT1("Device %x failed to stop!\n", DeviceData->AcpiHandle);
            status = STATUS_UNSUCCESSFUL;
            break;
        }

        state.DeviceState = PowerDeviceD3;
        PoSetPowerState(DeviceData->Common.Self, DevicePowerState, state);
        DeviceData->Common.DevicePowerState = PowerDeviceD3;
        SET_NEW_PNP_STATE(DeviceData->Common, Stopped);
        status = STATUS_SUCCESS;
        break;


    case IRP_MN_QUERY_STOP_DEVICE:

        //
        // No reason here why we can't stop the device.
        // If there were a reason we should speak now, because answering success
        // here may result in a stop device irp.
        //

        SET_NEW_PNP_STATE(DeviceData->Common, StopPending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_CANCEL_STOP_DEVICE:

        //
        // The stop was canceled.  Whatever state we set, or resources we put
        // on hold in anticipation of the forthcoming STOP device IRP should be
        // put back to normal.  Someone, in the long list of concerned parties,
        // has failed the stop device query.
        //

        //
        // First check to see whether you have received cancel-stop
        // without first receiving a query-stop. This could happen if someone
        // above us fails a query-stop and passes down the subsequent
        // cancel-stop.
        //

        if (StopPending == DeviceData->Common.DevicePnPState)
        {
            //
            // We did receive a query-stop, so restore.
            //
            RESTORE_PREVIOUS_PNP_STATE(DeviceData->Common);
        }
        status = STATUS_SUCCESS;// We must not fail this IRP.
        break;

    case IRP_MN_REMOVE_DEVICE:
        //
        // We handle REMOVE_DEVICE just like STOP_DEVICE. This is because
        // the device is still physically present (or at least we don't know any better)
        // so we have to retain the PDO after stopping and removing power from it.
        //
        if (DeviceData->InterfaceName.Length != 0)
            IoSetDeviceInterfaceState(&DeviceData->InterfaceName, FALSE);

        if (DeviceData->AcpiHandle && acpi_bus_power_manageable(DeviceData->AcpiHandle) &&
            !ACPI_SUCCESS(acpi_bus_set_power(DeviceData->AcpiHandle, ACPI_STATE_D3)))
        {
            DPRINT1("Device %x failed to enter D3!\n", DeviceData->AcpiHandle);
            state.DeviceState = PowerDeviceD3;
            PoSetPowerState(DeviceData->Common.Self, DevicePowerState, state);
            DeviceData->Common.DevicePowerState = PowerDeviceD3;
        }
        
        SET_NEW_PNP_STATE(DeviceData->Common, Stopped);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_QUERY_REMOVE_DEVICE:
        SET_NEW_PNP_STATE(DeviceData->Common, RemovalPending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_CANCEL_REMOVE_DEVICE:
        if (RemovalPending == DeviceData->Common.DevicePnPState)
        {
            RESTORE_PREVIOUS_PNP_STATE(DeviceData->Common);
        }
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_QUERY_CAPABILITIES:

        //
        // Return the capabilities of a device, such as whether the device
        // can be locked or ejected..etc
        //

        status = Bus_PDO_QueryDeviceCaps(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_ID:

        // Query the IDs of the device
        status = Bus_PDO_QueryDeviceId(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_DEVICE_RELATIONS:

        DPRINT("\tQueryDeviceRelation Type: %s\n",DbgDeviceRelationString(\
                    IrpStack->Parameters.QueryDeviceRelations.Type));

        status = Bus_PDO_QueryDeviceRelations(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_DEVICE_TEXT:

        status = Bus_PDO_QueryDeviceText(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_RESOURCES:

        status = Bus_PDO_QueryResources(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_RESOURCE_REQUIREMENTS:

        status = Bus_PDO_QueryResourceRequirements(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_BUS_INFORMATION:

        status = Bus_PDO_QueryBusInformation(DeviceData, Irp);

        break;

    case IRP_MN_QUERY_INTERFACE:

        status = Bus_PDO_QueryInterface(DeviceData, Irp);

        break;


    case IRP_MN_FILTER_RESOURCE_REQUIREMENTS:

        //
        // OPTIONAL for bus drivers.
        // The PnP Manager sends this IRP to a device
        // stack so filter and function drivers can adjust the
        // resources required by the device, if appropriate.
        //

        //break;

    //case IRP_MN_QUERY_PNP_DEVICE_STATE:

        //
        // OPTIONAL for bus drivers.
        // The PnP Manager sends this IRP after the drivers for
        // a device return success from the IRP_MN_START_DEVICE
        // request. The PnP Manager also sends this IRP when a
        // driver for the device calls IoInvalidateDeviceState.
        //

        // break;

    //case IRP_MN_READ_CONFIG:
    //case IRP_MN_WRITE_CONFIG:

        //
        // Bus drivers for buses with configuration space must handle
        // this request for their child devices. Our devices don't
        // have a config space.
        //

        // break;

    //case IRP_MN_SET_LOCK:

        // break;

    default:

        //
        // For PnP requests to the PDO that we do not understand we should
        // return the IRP WITHOUT setting the status or information fields.
        // These fields may have already been set by a filter (eg acpi).
        status = Irp->IoStatus.Status;

        break;
    }

    Irp->IoStatus.Status = status;
    IoCompleteRequest (Irp, IO_NO_INCREMENT);

    return status;
}