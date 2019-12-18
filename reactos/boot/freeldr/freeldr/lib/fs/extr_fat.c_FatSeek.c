#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UINT32 ;
struct TYPE_9__ {scalar_t__ HighPart; scalar_t__ LowPart; int /*<<< orphan*/  QuadPart; } ;
struct TYPE_8__ {scalar_t__ FilePointer; scalar_t__ FileSize; scalar_t__ CurrentCluster; scalar_t__ StartCluster; TYPE_1__* Volume; } ;
struct TYPE_7__ {scalar_t__ SectorsPerCluster; scalar_t__ BytesPerSector; } ;
typedef  int /*<<< orphan*/  SEEKMODE ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  TYPE_2__* PFAT_FILE_INFO ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatGetFatEntry (TYPE_1__*,scalar_t__,scalar_t__*) ; 
 TYPE_2__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
#define  SeekAbsolute 129 
#define  SeekRelative 128 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,...) ; 

ARC_STATUS FatSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    PFAT_FILE_INFO FileHandle = FsGetDeviceSpecific(FileId);
    PFAT_VOLUME_INFO Volume = FileHandle->Volume;
    LARGE_INTEGER NewPosition = *Position;

    switch (SeekMode)
    {
        case SeekAbsolute:
            break;
        case SeekRelative:
            NewPosition.QuadPart += (ULONGLONG)FileHandle->FilePointer;
            break;
        default:
            ASSERT(FALSE);
            return EINVAL;
    }

    if (NewPosition.HighPart != 0)
        return EINVAL;
    if (NewPosition.LowPart >= FileHandle->FileSize)
        return EINVAL;

    TRACE("FatSeek() NewPosition = %u, OldPointer = %u, SeekMode = %d\n", NewPosition.LowPart, FileHandle->FilePointer, SeekMode);

    {
        UINT32 OldClusterIdx = FileHandle->FilePointer / (Volume->SectorsPerCluster * Volume->BytesPerSector);
        UINT32 NewClusterIdx = NewPosition.LowPart / (Volume->SectorsPerCluster * Volume->BytesPerSector);

        TRACE("FatSeek() OldClusterIdx: %u, NewClusterIdx: %u\n", OldClusterIdx, NewClusterIdx);

        if (NewClusterIdx != OldClusterIdx)
        {
            UINT32 CurrentClusterIdx, ClusterNumber;

            if (NewClusterIdx > OldClusterIdx)
            {
                CurrentClusterIdx = OldClusterIdx;
                ClusterNumber = FileHandle->CurrentCluster;
            }
            else
            {
                CurrentClusterIdx = 0;
                ClusterNumber = FileHandle->StartCluster;
            }

            for (; CurrentClusterIdx < NewClusterIdx; CurrentClusterIdx++)
            {
                if (!FatGetFatEntry(Volume, ClusterNumber, &ClusterNumber))
                {
                    return EIO;
                }
            }
            FileHandle->CurrentCluster = ClusterNumber;
        }
    }

    FileHandle->FilePointer = NewPosition.LowPart;

    return ESUCCESS;
}