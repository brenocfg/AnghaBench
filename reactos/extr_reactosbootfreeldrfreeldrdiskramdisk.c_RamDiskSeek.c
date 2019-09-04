#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ HighPart; scalar_t__ LowPart; } ;
typedef  scalar_t__ SEEKMODE ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 scalar_t__ SeekAbsolute ; 
 scalar_t__ gRamDiskOffset ; 
 scalar_t__ gRamDiskSize ; 

__attribute__((used)) static ARC_STATUS RamDiskSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    //
    // Only accept absolute mode now
    //
    if (SeekMode != SeekAbsolute)
        return EINVAL;

    //
    // Check if we're in the ramdisk
    //
    if (Position->HighPart != 0)
        return EINVAL;
    if (Position->LowPart >= gRamDiskSize)
        return EINVAL;

    //
    // OK, remember seek position
    //
    gRamDiskOffset = Position->LowPart;

    return ESUCCESS;
}