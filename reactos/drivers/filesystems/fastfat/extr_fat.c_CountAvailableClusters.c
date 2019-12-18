#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ FatType; } ;
struct TYPE_11__ {int /*<<< orphan*/  FatResource; int /*<<< orphan*/  AvailableClusters; TYPE_1__ FatInfo; int /*<<< orphan*/  AvailableClustersValid; } ;
struct TYPE_10__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_2__* PLARGE_INTEGER ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ FAT12 ; 
 int /*<<< orphan*/  FAT12CountAvailableClusters (TYPE_3__*) ; 
 scalar_t__ FAT16 ; 
 int /*<<< orphan*/  FAT16CountAvailableClusters (TYPE_3__*) ; 
 int /*<<< orphan*/  FAT32CountAvailableClusters (TYPE_3__*) ; 
 scalar_t__ FATX16 ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
CountAvailableClusters(
    PDEVICE_EXTENSION DeviceExt,
    PLARGE_INTEGER Clusters)
{
    NTSTATUS Status = STATUS_SUCCESS;
    ExAcquireResourceExclusiveLite (&DeviceExt->FatResource, TRUE);
    if (!DeviceExt->AvailableClustersValid)
    {
        if (DeviceExt->FatInfo.FatType == FAT12)
            Status = FAT12CountAvailableClusters(DeviceExt);
        else if (DeviceExt->FatInfo.FatType == FAT16 || DeviceExt->FatInfo.FatType == FATX16)
            Status = FAT16CountAvailableClusters(DeviceExt);
        else
            Status = FAT32CountAvailableClusters(DeviceExt);
    }
    if (Clusters != NULL)
    {
        Clusters->QuadPart = DeviceExt->AvailableClusters;
    }
    ExReleaseResourceLite (&DeviceExt->FatResource);

    return Status;
}