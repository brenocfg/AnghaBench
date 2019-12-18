#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int ULONG ;
struct TYPE_6__ {int LowPart; } ;
struct TYPE_9__ {TYPE_1__ u; int /*<<< orphan*/  QuadPart; } ;
struct TYPE_7__ {int SectorsPerCluster; int /*<<< orphan*/  BytesPerSector; } ;
struct TYPE_8__ {TYPE_2__ NtfsInfo; int /*<<< orphan*/  StorageDevice; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NtfsReadSectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
ReadLCN(PDEVICE_EXTENSION Vcb,
        ULONGLONG lcn,
        ULONG count,
        PVOID buffer)
{
    LARGE_INTEGER DiskSector;

    DiskSector.QuadPart = lcn;

    return NtfsReadSectors(Vcb->StorageDevice,
                           DiskSector.u.LowPart * Vcb->NtfsInfo.SectorsPerCluster,
                           count * Vcb->NtfsInfo.SectorsPerCluster,
                           Vcb->NtfsInfo.BytesPerSector,
                           buffer,
                           FALSE);
}