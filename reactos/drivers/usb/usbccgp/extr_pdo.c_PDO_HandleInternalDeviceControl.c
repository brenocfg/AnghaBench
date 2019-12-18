#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  USB_DEVICE_DESCRIPTOR ;
struct TYPE_36__ {scalar_t__ DescriptorType; int TransferBufferLength; TYPE_9__* TransferBuffer; int /*<<< orphan*/  LanguageId; int /*<<< orphan*/  Index; } ;
struct TYPE_34__ {scalar_t__ Function; } ;
struct TYPE_41__ {TYPE_4__ UrbControlDescriptorRequest; TYPE_2__ UrbHeader; } ;
struct TYPE_40__ {int bLength; int /*<<< orphan*/ * bString; } ;
struct TYPE_39__ {void* Status; } ;
struct TYPE_37__ {int IoControlCode; int InputBufferLength; int OutputBufferLength; int Type3InputBuffer; } ;
struct TYPE_33__ {scalar_t__ Argument1; } ;
struct TYPE_38__ {TYPE_5__ DeviceIoControl; TYPE_1__ Others; } ;
struct TYPE_35__ {int /*<<< orphan*/  NextDeviceObject; } ;
struct TYPE_32__ {scalar_t__ DeviceExtension; } ;
struct TYPE_31__ {TYPE_6__ Parameters; } ;
struct TYPE_30__ {TYPE_7__ IoStatus; } ;
struct TYPE_29__ {int /*<<< orphan*/  NextDeviceObject; TYPE_3__* FDODeviceExtension; int /*<<< orphan*/  DeviceDescriptor; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_8__* PUSB_STRING_DESCRIPTOR ;
typedef  TYPE_9__* PURB ;
typedef  TYPE_10__* PPDO_DEVICE_EXTENSION ;
typedef  TYPE_11__* PIRP ;
typedef  TYPE_12__* PIO_STACK_LOCATION ;
typedef  TYPE_13__* PDEVICE_OBJECT ;
typedef  void* NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_9__*) ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 TYPE_9__* FALSE ; 
 int /*<<< orphan*/  FreeItem (TYPE_8__*) ; 
 int IOCTL_INTERNAL_USB_CYCLE_PORT ; 
 int IOCTL_INTERNAL_USB_GET_PORT_STATUS ; 
 int IOCTL_INTERNAL_USB_RESET_PORT ; 
 int IOCTL_INTERNAL_USB_SUBMIT_URB ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 void* IoCallDriver (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_11__*,int /*<<< orphan*/ ) ; 
 TYPE_12__* IoGetCurrentIrpStackLocation (TYPE_11__*) ; 
 int /*<<< orphan*/  IoSkipCurrentIrpStackLocation (TYPE_11__*) ; 
 scalar_t__ NT_SUCCESS (void*) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_9__*,int /*<<< orphan*/ *,int) ; 
 void* STATUS_DEVICE_DATA_ERROR ; 
 void* STATUS_INVALID_BUFFER_SIZE ; 
 void* STATUS_NOT_IMPLEMENTED ; 
 void* STATUS_SUCCESS ; 
 scalar_t__ URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE ; 
 scalar_t__ URB_FUNCTION_SELECT_CONFIGURATION ; 
 void* USBCCGP_BuildConfigurationDescriptor (TYPE_13__*,TYPE_11__*) ; 
 void* USBCCGP_GetDescriptor (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* USBCCGP_PDOSelectConfiguration (TYPE_13__*,TYPE_11__*) ; 
 scalar_t__ USB_CONFIGURATION_DESCRIPTOR_TYPE ; 
 scalar_t__ USB_DEVICE_DESCRIPTOR_TYPE ; 
 scalar_t__ USB_STRING_DESCRIPTOR_TYPE ; 

NTSTATUS
PDO_HandleInternalDeviceControl(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PIO_STACK_LOCATION IoStack;
    PPDO_DEVICE_EXTENSION PDODeviceExtension;
    NTSTATUS Status;
    PURB Urb;

    //
    // get current stack location
    //
    IoStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // get device extension
    //
    PDODeviceExtension = (PPDO_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

    if (IoStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_INTERNAL_USB_SUBMIT_URB)
    {
        //
        // get urb
        //
        Urb = (PURB)IoStack->Parameters.Others.Argument1;
        ASSERT(Urb);
        DPRINT("IOCTL_INTERNAL_USB_SUBMIT_URB Function %x\n", Urb->UrbHeader.Function);

        if (Urb->UrbHeader.Function == URB_FUNCTION_SELECT_CONFIGURATION)
        {
            //
            // select configuration
            //
            Status = USBCCGP_PDOSelectConfiguration(DeviceObject, Irp);
            Irp->IoStatus.Status = Status;
            IoCompleteRequest(Irp, IO_NO_INCREMENT);
            return Status;
        }
        else if (Urb->UrbHeader.Function == URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE)
        {
            if (Urb->UrbControlDescriptorRequest.DescriptorType == USB_DEVICE_DESCRIPTOR_TYPE)
            {
                //
                // is the buffer big enough
                //
                if (Urb->UrbControlDescriptorRequest.TransferBufferLength < sizeof(USB_DEVICE_DESCRIPTOR))
                {
                    //
                    // invalid buffer size
                    //
                    DPRINT1("[USBCCGP] invalid device descriptor size %lu\n", Urb->UrbControlDescriptorRequest.TransferBufferLength);
                    Urb->UrbControlDescriptorRequest.TransferBufferLength = sizeof(USB_DEVICE_DESCRIPTOR);
                    Irp->IoStatus.Status = STATUS_INVALID_BUFFER_SIZE;
                    IoCompleteRequest(Irp, IO_NO_INCREMENT);
                    return STATUS_INVALID_BUFFER_SIZE;
                }

                //
                // copy device descriptor
                //
                ASSERT(Urb->UrbControlDescriptorRequest.TransferBuffer);
                RtlCopyMemory(Urb->UrbControlDescriptorRequest.TransferBuffer, &PDODeviceExtension->DeviceDescriptor, sizeof(USB_DEVICE_DESCRIPTOR));
                Irp->IoStatus.Status = STATUS_SUCCESS;
                IoCompleteRequest(Irp, IO_NO_INCREMENT);
                return STATUS_SUCCESS;
            }
            else if (Urb->UrbControlDescriptorRequest.DescriptorType == USB_CONFIGURATION_DESCRIPTOR_TYPE)
            {
                //
                // build configuration descriptor
                //
                Status = USBCCGP_BuildConfigurationDescriptor(DeviceObject, Irp);
                Irp->IoStatus.Status = Status;
                IoCompleteRequest(Irp, IO_NO_INCREMENT);
                return Status;
            }
            else if (Urb->UrbControlDescriptorRequest.DescriptorType == USB_STRING_DESCRIPTOR_TYPE)
            {
                PUSB_STRING_DESCRIPTOR StringDescriptor;

                //
                // get the requested string descriptor
                //
                ASSERT(Urb->UrbControlDescriptorRequest.TransferBuffer);
                Status = USBCCGP_GetDescriptor(PDODeviceExtension->FDODeviceExtension->NextDeviceObject,
                                               USB_STRING_DESCRIPTOR_TYPE,
                                               Urb->UrbControlDescriptorRequest.TransferBufferLength,
                                               Urb->UrbControlDescriptorRequest.Index,
                                               Urb->UrbControlDescriptorRequest.LanguageId,
                                               (PVOID*)&StringDescriptor);
                if (NT_SUCCESS(Status))
                {
                    if (StringDescriptor->bLength == 2)
                    {
                        FreeItem(StringDescriptor);
                        Status = STATUS_DEVICE_DATA_ERROR;
                    }
                    else
                    {
                        RtlCopyMemory(Urb->UrbControlDescriptorRequest.TransferBuffer,
                                      StringDescriptor->bString,
                                      StringDescriptor->bLength + sizeof(WCHAR));
                        FreeItem(StringDescriptor);
                        Status = STATUS_SUCCESS;
                    }
                }
                Irp->IoStatus.Status = Status;
                IoCompleteRequest(Irp, IO_NO_INCREMENT);
                return Status;
            }
        }
        else
        {
            IoSkipCurrentIrpStackLocation(Irp);
            Status = IoCallDriver(PDODeviceExtension->NextDeviceObject, Irp);
            return Status;
        }
    }
    else if (IoStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_INTERNAL_USB_GET_PORT_STATUS)
    {
        IoSkipCurrentIrpStackLocation(Irp);
        Status = IoCallDriver(PDODeviceExtension->NextDeviceObject, Irp);
        return Status;
    }
    else if (IoStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_INTERNAL_USB_RESET_PORT)
    {
        IoSkipCurrentIrpStackLocation(Irp);
        Status = IoCallDriver(PDODeviceExtension->NextDeviceObject, Irp);
        return Status;
    }
    else if (IoStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_INTERNAL_USB_CYCLE_PORT)
    {
        IoSkipCurrentIrpStackLocation(Irp);
        Status = IoCallDriver(PDODeviceExtension->NextDeviceObject, Irp);
        return Status;
    }

    DPRINT1("IOCTL %x\n", IoStack->Parameters.DeviceIoControl.IoControlCode);
    DPRINT1("InputBufferLength %lu\n", IoStack->Parameters.DeviceIoControl.InputBufferLength);
    DPRINT1("OutputBufferLength %lu\n", IoStack->Parameters.DeviceIoControl.OutputBufferLength);
    DPRINT1("Type3InputBuffer %p\n", IoStack->Parameters.DeviceIoControl.Type3InputBuffer);

    ASSERT(FALSE);

    Irp->IoStatus.Status = STATUS_NOT_IMPLEMENTED;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return STATUS_NOT_IMPLEMENTED;
}