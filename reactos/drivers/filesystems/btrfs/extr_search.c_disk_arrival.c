#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gli ;
typedef  int ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_9__ {scalar_t__ PartitionCount; int DeviceNumber; TYPE_1__ Length; scalar_t__ PartitionNumber; int /*<<< orphan*/  DeviceType; } ;
typedef  TYPE_2__ STORAGE_DEVICE_NUMBER ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDRIVER_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  TYPE_2__ GET_LENGTH_INFORMATION ;
typedef  TYPE_2__ DRIVE_LAYOUT_INFORMATION_EX ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_2__*) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_DRIVE_LAYOUT_EX ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_LENGTH_INFO ; 
 int /*<<< orphan*/  IOCTL_STORAGE_GET_DEVICE_NUMBER ; 
 scalar_t__ IoGetDeviceObjectPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_lock ; 
 scalar_t__ dev_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_vol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

void disk_arrival(PDRIVER_OBJECT DriverObject, PUNICODE_STRING devpath) {
    PFILE_OBJECT fileobj;
    PDEVICE_OBJECT devobj;
    NTSTATUS Status;
    STORAGE_DEVICE_NUMBER sdn;
    ULONG dlisize;
    DRIVE_LAYOUT_INFORMATION_EX* dli = NULL;
    IO_STATUS_BLOCK iosb;
    GET_LENGTH_INFORMATION gli;

    UNUSED(DriverObject);

    ExAcquireResourceSharedLite(&boot_lock, TRUE);

    Status = IoGetDeviceObjectPointer(devpath, FILE_READ_ATTRIBUTES, &fileobj, &devobj);
    if (!NT_SUCCESS(Status)) {
        ExReleaseResourceLite(&boot_lock);
        ERR("IoGetDeviceObjectPointer returned %08x\n", Status);
        return;
    }

    dlisize = 0;

    do {
        dlisize += 1024;

        if (dli)
            ExFreePool(dli);

        dli = ExAllocatePoolWithTag(PagedPool, dlisize, ALLOC_TAG);
        if (!dli) {
            ERR("out of memory\n");
            goto end;
        }

        Status = dev_ioctl(devobj, IOCTL_DISK_GET_DRIVE_LAYOUT_EX, NULL, 0,
                           dli, dlisize, true, &iosb);
    } while (Status == STATUS_BUFFER_TOO_SMALL);

    // only consider disk as a potential filesystem if it has no partitions
    if (NT_SUCCESS(Status) && dli->PartitionCount > 0) {
        ExFreePool(dli);
        goto end;
    }

    ExFreePool(dli);

    Status = dev_ioctl(devobj, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0,
                        &gli, sizeof(gli), true, NULL);

    if (!NT_SUCCESS(Status)) {
        ERR("error reading length information: %08x\n", Status);
        goto end;
    }

    Status = dev_ioctl(devobj, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0,
                       &sdn, sizeof(STORAGE_DEVICE_NUMBER), true, NULL);
    if (!NT_SUCCESS(Status)) {
        TRACE("IOCTL_STORAGE_GET_DEVICE_NUMBER returned %08x\n", Status);
        sdn.DeviceNumber = 0xffffffff;
        sdn.PartitionNumber = 0;
    } else
        TRACE("DeviceType = %u, DeviceNumber = %u, PartitionNumber = %u\n", sdn.DeviceType, sdn.DeviceNumber, sdn.PartitionNumber);

    test_vol(devobj, fileobj, devpath, sdn.DeviceNumber, sdn.PartitionNumber, gli.Length.QuadPart);

end:
    ObDereferenceObject(fileobj);

    ExReleaseResourceLite(&boot_lock);
}