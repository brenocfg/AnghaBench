#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_20__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
struct TYPE_35__ {int rootDirectorySectors; int BytesPerSector; int BytesPerCluster; } ;
struct TYPE_33__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_32__ {int QuadPart; } ;
struct TYPE_31__ {int QuadPart; } ;
struct TYPE_34__ {TYPE_7__ AllocationSize; TYPE_6__ ValidDataLength; TYPE_5__ FileSize; } ;
struct TYPE_30__ {int FileSize; } ;
struct TYPE_29__ {int FileSize; } ;
struct TYPE_28__ {void* Hash; } ;
struct TYPE_27__ {TYPE_4__ Fat; TYPE_3__ FatX; } ;
struct TYPE_26__ {void* Hash; } ;
struct TYPE_25__ {TYPE_9__ FatInfo; } ;
struct TYPE_24__ {int dirIndex; int startIndex; TYPE_8__ RFCB; TYPE_20__ entry; int /*<<< orphan*/  ShortNameU; TYPE_2__ ShortHash; int /*<<< orphan*/  DirNameU; TYPE_1__ Hash; int /*<<< orphan*/  PathNameU; } ;
struct TYPE_23__ {int DirIndex; int StartIndex; int /*<<< orphan*/  ShortNameU; int /*<<< orphan*/  DirEntry; } ;
typedef  TYPE_10__* PVFAT_DIRENTRY_CONTEXT ;
typedef  TYPE_11__* PVFATFCB ;
typedef  TYPE_12__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DIR_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NextCluster (TYPE_12__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUND_UP_64 (int,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_20__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlCopyUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int vfatDirEntryGetFirstCluster (TYPE_12__*,TYPE_20__*) ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_11__*) ; 
 int /*<<< orphan*/  vfatFCBIsRoot (TYPE_11__*) ; 
 void* vfatNameHash (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ vfatVolumeIsFatX (TYPE_12__*) ; 

__attribute__((used)) static
VOID
vfatInitFCBFromDirEntry(
    PDEVICE_EXTENSION Vcb,
    PVFATFCB Fcb,
    PVFAT_DIRENTRY_CONTEXT DirContext)
{
    ULONG Size;

    RtlCopyMemory(&Fcb->entry, &DirContext->DirEntry, sizeof (DIR_ENTRY));
    RtlCopyUnicodeString(&Fcb->ShortNameU, &DirContext->ShortNameU);
    Fcb->Hash.Hash = vfatNameHash(0, &Fcb->PathNameU);
    if (vfatVolumeIsFatX(Vcb))
    {
        Fcb->ShortHash.Hash = Fcb->Hash.Hash;
    }
    else
    {
        Fcb->ShortHash.Hash = vfatNameHash(0, &Fcb->DirNameU);
        Fcb->ShortHash.Hash = vfatNameHash(Fcb->ShortHash.Hash, &Fcb->ShortNameU);
    }

    if (vfatFCBIsDirectory(Fcb))
    {
        ULONG FirstCluster, CurrentCluster;
        NTSTATUS Status = STATUS_SUCCESS;
        Size = 0;
        FirstCluster = vfatDirEntryGetFirstCluster(Vcb, &Fcb->entry);
        if (FirstCluster == 1)
        {
            Size = Vcb->FatInfo.rootDirectorySectors * Vcb->FatInfo.BytesPerSector;
        }
        else if (FirstCluster != 0)
        {
            CurrentCluster = FirstCluster;
            while (CurrentCluster != 0xffffffff && NT_SUCCESS(Status))
            {
                Size += Vcb->FatInfo.BytesPerCluster;
                Status = NextCluster(Vcb, FirstCluster, &CurrentCluster, FALSE);
            }
        }
    }
    else if (vfatVolumeIsFatX(Vcb))
    {
        Size = Fcb->entry.FatX.FileSize;
    }
    else
    {
        Size = Fcb->entry.Fat.FileSize;
    }
    Fcb->dirIndex = DirContext->DirIndex;
    Fcb->startIndex = DirContext->StartIndex;
    if (vfatVolumeIsFatX(Vcb) && !vfatFCBIsRoot(Fcb))
    {
        ASSERT(DirContext->DirIndex >= 2 && DirContext->StartIndex >= 2);
        Fcb->dirIndex = DirContext->DirIndex-2;
        Fcb->startIndex = DirContext->StartIndex-2;
    }
    Fcb->RFCB.FileSize.QuadPart = Size;
    Fcb->RFCB.ValidDataLength.QuadPart = Size;
    Fcb->RFCB.AllocationSize.QuadPart = ROUND_UP_64(Size, Vcb->FatInfo.BytesPerCluster);
}