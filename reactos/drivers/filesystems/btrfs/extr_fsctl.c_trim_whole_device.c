#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  devobj; } ;
typedef  TYPE_1__ device ;
struct TYPE_6__ {int Size; int Flags; scalar_t__ DataSetRangesLength; scalar_t__ DataSetRangesOffset; scalar_t__ ParameterBlockLength; scalar_t__ ParameterBlockOffset; int /*<<< orphan*/  Action; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ DEVICE_MANAGE_DATA_SET_ATTRIBUTES ;

/* Variables and functions */
 int DEVICE_DSM_FLAG_ENTIRE_DATA_SET_RANGE ; 
 int DEVICE_DSM_FLAG_TRIM_NOT_FS_ALLOCATED ; 
 int /*<<< orphan*/  DeviceDsmAction_Trim ; 
 int /*<<< orphan*/  IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void trim_whole_device(device* dev) {
    DEVICE_MANAGE_DATA_SET_ATTRIBUTES dmdsa;
    NTSTATUS Status;

    // FIXME - avoid "bootloader area"??

    dmdsa.Size = sizeof(DEVICE_MANAGE_DATA_SET_ATTRIBUTES);
    dmdsa.Action = DeviceDsmAction_Trim;
    dmdsa.Flags = DEVICE_DSM_FLAG_ENTIRE_DATA_SET_RANGE | DEVICE_DSM_FLAG_TRIM_NOT_FS_ALLOCATED;
    dmdsa.ParameterBlockOffset = 0;
    dmdsa.ParameterBlockLength = 0;
    dmdsa.DataSetRangesOffset = 0;
    dmdsa.DataSetRangesLength = 0;

    Status = dev_ioctl(dev->devobj, IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES, &dmdsa, sizeof(DEVICE_MANAGE_DATA_SET_ATTRIBUTES), NULL, 0, true, NULL);
    if (!NT_SUCCESS(Status))
        WARN("IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES returned %08x\n", Status);
}