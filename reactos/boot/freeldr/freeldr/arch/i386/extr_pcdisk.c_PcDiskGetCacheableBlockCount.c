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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int Sectors; } ;
typedef  TYPE_1__ GEOMETRY ;

/* Variables and functions */
 scalar_t__ DiskInt13ExtensionsSupported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PcDiskGetDriveGeometry (int /*<<< orphan*/ ,TYPE_1__*) ; 

ULONG
PcDiskGetCacheableBlockCount(UCHAR DriveNumber)
{
    GEOMETRY Geometry;

    /* If LBA is supported then the block size will be 64 sectors (32k)
     * If not then the block size is the size of one track. */
    if (DiskInt13ExtensionsSupported(DriveNumber))
    {
        return 64;
    }
    /* Get the disk geometry. If this fails then we will
     * just return 1 sector to be safe. */
    else if (!PcDiskGetDriveGeometry(DriveNumber, &Geometry))
    {
        return 1;
    }
    else
    {
        return Geometry.Sectors;
    }
}