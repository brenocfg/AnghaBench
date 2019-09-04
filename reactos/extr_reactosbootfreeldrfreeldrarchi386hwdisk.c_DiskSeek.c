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
struct TYPE_6__ {int SectorSize; int SectorNumber; } ;
struct TYPE_5__ {int LowPart; int QuadPart; } ;
typedef  scalar_t__ SEEKMODE ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ DISKCONTEXT ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_2__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
 scalar_t__ SeekAbsolute ; 

__attribute__((used)) static ARC_STATUS
DiskSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    DISKCONTEXT* Context = FsGetDeviceSpecific(FileId);

    if (SeekMode != SeekAbsolute)
        return EINVAL;
    if (Position->LowPart & (Context->SectorSize - 1))
        return EINVAL;

    Context->SectorNumber = Position->QuadPart / Context->SectorSize;
    return ESUCCESS;
}