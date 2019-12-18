#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
struct TYPE_7__ {scalar_t__ Offset; TYPE_1__* DataContext; } ;
struct TYPE_6__ {int /*<<< orphan*/  Record; } ;
typedef  int SEEKMODE ;
typedef  TYPE_2__* PNTFS_FILE_HANDLE ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
 scalar_t__ NtfsGetAttributeSize (int /*<<< orphan*/ *) ; 
#define  SeekAbsolute 129 
#define  SeekRelative 128 

ARC_STATUS NtfsSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    PNTFS_FILE_HANDLE FileHandle = FsGetDeviceSpecific(FileId);
    LARGE_INTEGER NewPosition = *Position;

    switch (SeekMode)
    {
        case SeekAbsolute:
            break;
        case SeekRelative:
            NewPosition.QuadPart += FileHandle->Offset;
            break;
        default:
            ASSERT(FALSE);
            return EINVAL;
    }

    if (NewPosition.QuadPart >= NtfsGetAttributeSize(&FileHandle->DataContext->Record))
        return EINVAL;

    FileHandle->Offset = NewPosition.QuadPart;
    return ESUCCESS;
}