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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ magic; } ;
struct TYPE_5__ {int LowPart; scalar_t__ HighPart; } ;
typedef  int /*<<< orphan*/  SuperBlock ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ EXT2_SUPER_BLOCK ;
typedef  int /*<<< orphan*/  DEVVTBL ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ ArcRead (int,TYPE_2__*,int,int*) ; 
 scalar_t__ ArcSeek (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DiskGetBootVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ESUCCESS ; 
 scalar_t__ EXT2_MAGIC ; 
 int /*<<< orphan*/  const Ext2FuncTable ; 
 int /*<<< orphan*/  Ext2OpenVolume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekAbsolute ; 

const DEVVTBL* Ext2Mount(ULONG DeviceId)
{
    EXT2_SUPER_BLOCK SuperBlock;
    LARGE_INTEGER Position;
    ULONG Count;
    ARC_STATUS Status;

    //
    // Read the SuperBlock
    //
    Position.HighPart = 0;
    Position.LowPart = 2 * 512;
    Status = ArcSeek(DeviceId, &Position, SeekAbsolute);
    if (Status != ESUCCESS)
        return NULL;
    Status = ArcRead(DeviceId, &SuperBlock, sizeof(SuperBlock), &Count);
    if (Status != ESUCCESS || Count != sizeof(SuperBlock))
        return NULL;

    //
    // Check if SuperBlock is valid. If yes, return Ext2 function table
    //
    if (SuperBlock.magic == EXT2_MAGIC)
    {
        //
        // Compatibility hack as long as FS is not using underlying device DeviceId
        //
        UCHAR DriveNumber;
        ULONGLONG StartSector;
        ULONGLONG SectorCount;
        int Type;
        if (!DiskGetBootVolume(&DriveNumber, &StartSector, &SectorCount, &Type))
            return NULL;
        Ext2OpenVolume(DriveNumber, StartSector, SectorCount);
        return &Ext2FuncTable;
    }
    else
        return NULL;
}