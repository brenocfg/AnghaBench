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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {scalar_t__ HighPart; scalar_t__ LowPart; int /*<<< orphan*/  QuadPart; } ;
struct TYPE_5__ {scalar_t__ FilePointer; scalar_t__ FileSize; } ;
typedef  int SEEKMODE ;
typedef  TYPE_1__* PISO_FILE_INFO ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
#define  SeekAbsolute 129 
#define  SeekRelative 128 

ARC_STATUS IsoSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    PISO_FILE_INFO FileHandle = FsGetDeviceSpecific(FileId);
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

    FileHandle->FilePointer = NewPosition.LowPart;
    return ESUCCESS;
}