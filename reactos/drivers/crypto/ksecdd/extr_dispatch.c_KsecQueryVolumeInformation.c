#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ Characteristics; int /*<<< orphan*/  DeviceType; } ;
typedef  scalar_t__ PVOID ;
typedef  int* PSIZE_T ;
typedef  TYPE_1__* PFILE_FS_DEVICE_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ FS_INFORMATION_CLASS ;
typedef  int /*<<< orphan*/  FILE_FS_DEVICE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_DEVICE_NULL ; 
 scalar_t__ FileFsDeviceInformation ; 
 int /*<<< orphan*/  STATUS_INFO_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  STATUS_INVALID_INFO_CLASS ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
KsecQueryVolumeInformation(
    PVOID InfoBuffer,
    FS_INFORMATION_CLASS FsInformationClass,
    PSIZE_T BufferLength)
{
    PFILE_FS_DEVICE_INFORMATION DeviceInformation;

    /* Only FileFsDeviceInformation is supported */
    if (FsInformationClass != FileFsDeviceInformation)
    {
        return STATUS_INVALID_INFO_CLASS;
    }

    /* Validate buffer size */
    if (*BufferLength < sizeof(FILE_FS_DEVICE_INFORMATION))
    {
        *BufferLength = sizeof(FILE_FS_DEVICE_INFORMATION);
        return STATUS_INFO_LENGTH_MISMATCH;
    }

    /* Fill the structure */
    DeviceInformation = (PFILE_FS_DEVICE_INFORMATION)InfoBuffer;
    DeviceInformation->DeviceType = FILE_DEVICE_NULL;
    DeviceInformation->Characteristics = 0;
    *BufferLength = sizeof(FILE_FS_DEVICE_INFORMATION);

    return STATUS_SUCCESS;
}