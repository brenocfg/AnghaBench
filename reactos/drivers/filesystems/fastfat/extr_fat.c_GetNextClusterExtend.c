#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  FatResource; int /*<<< orphan*/  (* FindAndMarkAvailableCluster ) (TYPE_1__*,scalar_t__*) ;int /*<<< orphan*/  (* GetNextCluster ) (TYPE_1__*,scalar_t__,int*) ;} ;
typedef  int* PULONG ;
typedef  TYPE_1__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteCluster (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,scalar_t__*) ; 

NTSTATUS
GetNextClusterExtend(
    PDEVICE_EXTENSION DeviceExt,
    ULONG CurrentCluster,
    PULONG NextCluster)
{
    ULONG NewCluster;
    NTSTATUS Status;

    DPRINT("GetNextClusterExtend(DeviceExt %p, CurrentCluster %x)\n",
           DeviceExt, CurrentCluster);

    ExAcquireResourceExclusiveLite(&DeviceExt->FatResource, TRUE);
    /*
     * If the file hasn't any clusters allocated then we need special
     * handling
     */
    if (CurrentCluster == 0)
    {
        Status = DeviceExt->FindAndMarkAvailableCluster(DeviceExt, &NewCluster);
        if (!NT_SUCCESS(Status))
        {
            ExReleaseResourceLite(&DeviceExt->FatResource);
            return Status;
        }

        *NextCluster = NewCluster;
        ExReleaseResourceLite(&DeviceExt->FatResource);
        return STATUS_SUCCESS;
    }

    Status = DeviceExt->GetNextCluster(DeviceExt, CurrentCluster, NextCluster);

    if ((*NextCluster) == 0xFFFFFFFF)
    {
        /* We are after last existing cluster, we must add one to file */
        /* Firstly, find the next available open allocation unit and
           mark it as end of file */
        Status = DeviceExt->FindAndMarkAvailableCluster(DeviceExt, &NewCluster);
        if (!NT_SUCCESS(Status))
        {
            ExReleaseResourceLite(&DeviceExt->FatResource);
            return Status;
        }

        /* Now, write the AU of the LastCluster with the value of the newly
           found AU */
        WriteCluster(DeviceExt, CurrentCluster, NewCluster);
        *NextCluster = NewCluster;
    }

    ExReleaseResourceLite(&DeviceExt->FatResource);
    return Status;
}