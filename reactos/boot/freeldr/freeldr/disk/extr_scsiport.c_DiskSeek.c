#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int SectorNumber; int SectorSize; int SectorCount; } ;
struct TYPE_5__ {int QuadPart; } ;
typedef  int SEEKMODE ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ DISKCONTEXT ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
#define  SeekAbsolute 129 
#define  SeekRelative 128 

__attribute__((used)) static ARC_STATUS DiskSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    DISKCONTEXT* Context = FsGetDeviceSpecific(FileId);
    LARGE_INTEGER NewPosition = *Position;

    switch (SeekMode)
    {
        case SeekAbsolute:
            break;
        case SeekRelative:
            NewPosition.QuadPart += (Context->SectorNumber * Context->SectorSize);
            break;
        default:
            ASSERT(FALSE);
            return EINVAL;
    }

    if (NewPosition.QuadPart & (Context->SectorSize - 1))
        return EINVAL;

    /* Convert in number of sectors */
    NewPosition.QuadPart /= Context->SectorSize;
    if (NewPosition.QuadPart >= Context->SectorCount)
        return EINVAL;

    Context->SectorNumber = NewPosition.QuadPart;
    return ESUCCESS;
}