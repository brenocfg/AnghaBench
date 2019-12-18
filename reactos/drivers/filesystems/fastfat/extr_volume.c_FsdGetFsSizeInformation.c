#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  BytesPerSector; int /*<<< orphan*/  SectorsPerCluster; int /*<<< orphan*/  NumberOfClusters; } ;
struct TYPE_13__ {TYPE_2__ FatInfo; } ;
struct TYPE_12__ {TYPE_5__* DeviceExtension; } ;
struct TYPE_9__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_11__ {int /*<<< orphan*/  BytesPerSector; int /*<<< orphan*/  SectorsPerAllocationUnit; TYPE_1__ TotalAllocationUnits; int /*<<< orphan*/  AvailableAllocationUnits; } ;
typedef  int* PULONG ;
typedef  TYPE_3__* PFILE_FS_SIZE_INFORMATION ;
typedef  TYPE_4__* PDEVICE_OBJECT ;
typedef  TYPE_5__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_FS_SIZE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CountAvailableClusters (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
FsdGetFsSizeInformation(
    PDEVICE_OBJECT DeviceObject,
    PFILE_FS_SIZE_INFORMATION FsSizeInfo,
    PULONG BufferLength)
{
    PDEVICE_EXTENSION DeviceExt;
    NTSTATUS Status;

    DPRINT("FsdGetFsSizeInformation()\n");
    DPRINT("FsSizeInfo = %p\n", FsSizeInfo);

    ASSERT(*BufferLength >= sizeof(FILE_FS_SIZE_INFORMATION));

    DeviceExt = DeviceObject->DeviceExtension;
    Status = CountAvailableClusters(DeviceExt, &FsSizeInfo->AvailableAllocationUnits);

    FsSizeInfo->TotalAllocationUnits.QuadPart = DeviceExt->FatInfo.NumberOfClusters;
    FsSizeInfo->SectorsPerAllocationUnit = DeviceExt->FatInfo.SectorsPerCluster;
    FsSizeInfo->BytesPerSector = DeviceExt->FatInfo.BytesPerSector;

    DPRINT("Finished FsdGetFsSizeInformation()\n");
    if (NT_SUCCESS(Status))
        *BufferLength -= sizeof(FILE_FS_SIZE_INFORMATION);

    return Status;
}