#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/ * KsecDeviceHandle ; 
 int /*<<< orphan*/  KsecOpenDevice () ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
KsecDeviceIoControl(
    ULONG IoControlCode,
    PVOID InputBuffer,
    SIZE_T InputBufferLength,
    PVOID OutputBuffer,
    SIZE_T OutputBufferLength)
{
    IO_STATUS_BLOCK IoStatusBlock;
    NTSTATUS Status;

    /* Check if we already have a handle */
    if (KsecDeviceHandle == NULL)
    {
        /* Try to open the device */
        Status = KsecOpenDevice();
        if (!NT_SUCCESS(Status))
        {
            //ERR("Failed to open handle to KsecDd driver!\n");
            return Status;
        }
    }

    /* Call the driver */
    Status = NtDeviceIoControlFile(KsecDeviceHandle,
                                   NULL,
                                   NULL,
                                   NULL,
                                   &IoStatusBlock,
                                   IoControlCode,
                                   InputBuffer,
                                   InputBufferLength,
                                   OutputBuffer,
                                   OutputBufferLength);

    return Status;
}