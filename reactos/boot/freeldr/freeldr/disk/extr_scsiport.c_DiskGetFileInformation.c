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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_13__ {int SectorOffset; int SectorSize; int SectorCount; int SectorNumber; } ;
struct TYPE_9__ {int QuadPart; } ;
struct TYPE_11__ {int QuadPart; } ;
struct TYPE_10__ {int QuadPart; } ;
struct TYPE_12__ {TYPE_1__ CurrentAddress; TYPE_3__ EndingAddress; TYPE_2__ StartingAddress; } ;
typedef  TYPE_4__ FILEINFORMATION ;
typedef  TYPE_5__ DISKCONTEXT ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_5__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,int) ; 

__attribute__((used)) static ARC_STATUS DiskGetFileInformation(ULONG FileId, FILEINFORMATION* Information)
{
    DISKCONTEXT* Context = FsGetDeviceSpecific(FileId);

    RtlZeroMemory(Information, sizeof(*Information));

    /*
     * The ARC specification mentions that for partitions, StartingAddress and
     * EndingAddress are the start and end positions of the partition in terms
     * of byte offsets from the start of the disk.
     * CurrentAddress is the current offset into (i.e. relative to) the partition.
     */
    Information->StartingAddress.QuadPart = Context->SectorOffset * Context->SectorSize;
    Information->EndingAddress.QuadPart   = (Context->SectorOffset + Context->SectorCount) * Context->SectorSize;
    Information->CurrentAddress.QuadPart  = Context->SectorNumber * Context->SectorSize;

    return ESUCCESS;
}