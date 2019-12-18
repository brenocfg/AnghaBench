#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  FatResource; int /*<<< orphan*/  AvailableClusters; scalar_t__ AvailableClustersValid; int /*<<< orphan*/  (* WriteCluster ) (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ;} ;
typedef  int /*<<< orphan*/  PLONG ;
typedef  TYPE_1__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ; 

NTSTATUS
WriteCluster(
    PDEVICE_EXTENSION DeviceExt,
    ULONG ClusterToWrite,
    ULONG NewValue)
{
    NTSTATUS Status;
    ULONG OldValue;

    ExAcquireResourceExclusiveLite (&DeviceExt->FatResource, TRUE);
    Status = DeviceExt->WriteCluster(DeviceExt, ClusterToWrite, NewValue, &OldValue);
    if (DeviceExt->AvailableClustersValid)
    {
        if (OldValue && NewValue == 0)
            InterlockedIncrement((PLONG)&DeviceExt->AvailableClusters);
        else if (OldValue == 0 && NewValue)
            InterlockedDecrement((PLONG)&DeviceExt->AvailableClusters);
    }
    ExReleaseResourceLite(&DeviceExt->FatResource);
    return Status;
}