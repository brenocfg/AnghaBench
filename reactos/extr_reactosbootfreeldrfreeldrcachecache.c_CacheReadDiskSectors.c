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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {scalar_t__ BlockSize; scalar_t__ BytesPerSector; } ;
struct TYPE_5__ {scalar_t__ BlockData; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PCACHE_BLOCK ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_1__* CacheInternalGetBlockPointer (TYPE_2__*,scalar_t__) ; 
 TYPE_2__ CacheManagerDrive ; 
 scalar_t__ CacheManagerInitialized ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 scalar_t__ TRUE ; 

BOOLEAN CacheReadDiskSectors(UCHAR DiskNumber, ULONGLONG StartSector, ULONG SectorCount, PVOID Buffer)
{
    PCACHE_BLOCK    CacheBlock;
    ULONG                StartBlock;
    ULONG                SectorOffsetInStartBlock;
    ULONG                CopyLengthInStartBlock;
    ULONG                EndBlock;
    ULONG                SectorOffsetInEndBlock;
    ULONG                BlockCount;
    ULONG                Idx;

    TRACE("CacheReadDiskSectors() DiskNumber: 0x%x StartSector: %I64d SectorCount: %d Buffer: 0x%x\n", DiskNumber, StartSector, SectorCount, Buffer);

    // If we aren't initialized yet then they can't do this
    if (CacheManagerInitialized == FALSE)
    {
        return FALSE;
    }

    //
    // Calculate which blocks we must cache
    //
    StartBlock = (ULONG)(StartSector / CacheManagerDrive.BlockSize);
    SectorOffsetInStartBlock = (ULONG)(StartSector % CacheManagerDrive.BlockSize);
    CopyLengthInStartBlock = (ULONG)((SectorCount > (CacheManagerDrive.BlockSize - SectorOffsetInStartBlock)) ? (CacheManagerDrive.BlockSize - SectorOffsetInStartBlock) : SectorCount);
    EndBlock = (ULONG)((StartSector + (SectorCount - 1)) / CacheManagerDrive.BlockSize);
    SectorOffsetInEndBlock = (ULONG)(1 + (StartSector + (SectorCount - 1)) % CacheManagerDrive.BlockSize);
    BlockCount = (EndBlock - StartBlock) + 1;
    TRACE("StartBlock: %d SectorOffsetInStartBlock: %d CopyLengthInStartBlock: %d EndBlock: %d SectorOffsetInEndBlock: %d BlockCount: %d\n", StartBlock, SectorOffsetInStartBlock, CopyLengthInStartBlock, EndBlock, SectorOffsetInEndBlock, BlockCount);

    //
    // Read the first block into the buffer
    //
    if (BlockCount > 0)
    {
        //
        // Get cache block pointer (this forces the disk sectors into the cache memory)
        //
        CacheBlock = CacheInternalGetBlockPointer(&CacheManagerDrive, StartBlock);
        if (CacheBlock == NULL)
        {
            return FALSE;
        }

        //
        // Copy the portion requested into the buffer
        //
        RtlCopyMemory(Buffer,
            (PVOID)((ULONG_PTR)CacheBlock->BlockData + (SectorOffsetInStartBlock * CacheManagerDrive.BytesPerSector)),
            (CopyLengthInStartBlock * CacheManagerDrive.BytesPerSector));
        TRACE("1 - RtlCopyMemory(0x%x, 0x%x, %d)\n", Buffer, ((ULONG_PTR)CacheBlock->BlockData + (SectorOffsetInStartBlock * CacheManagerDrive.BytesPerSector)), (CopyLengthInStartBlock * CacheManagerDrive.BytesPerSector));

        //
        // Update the buffer address
        //
        Buffer = (PVOID)((ULONG_PTR)Buffer + (CopyLengthInStartBlock * CacheManagerDrive.BytesPerSector));

        //
        // Update the block count
        //
        BlockCount--;
    }

    //
    // Loop through the middle blocks and read them into the buffer
    //
    for (Idx=StartBlock+1; BlockCount>1; Idx++)
    {
        //
        // Get cache block pointer (this forces the disk sectors into the cache memory)
        //
        CacheBlock = CacheInternalGetBlockPointer(&CacheManagerDrive, Idx);
        if (CacheBlock == NULL)
        {
            return FALSE;
        }

        //
        // Copy the portion requested into the buffer
        //
        RtlCopyMemory(Buffer,
            CacheBlock->BlockData,
            CacheManagerDrive.BlockSize * CacheManagerDrive.BytesPerSector);
        TRACE("2 - RtlCopyMemory(0x%x, 0x%x, %d)\n", Buffer, CacheBlock->BlockData, CacheManagerDrive.BlockSize * CacheManagerDrive.BytesPerSector);

        //
        // Update the buffer address
        //
        Buffer = (PVOID)((ULONG_PTR)Buffer + (CacheManagerDrive.BlockSize * CacheManagerDrive.BytesPerSector));

        //
        // Update the block count
        //
        BlockCount--;
    }

    //
    // Read the last block into the buffer
    //
    if (BlockCount > 0)
    {
        //
        // Get cache block pointer (this forces the disk sectors into the cache memory)
        //
        CacheBlock = CacheInternalGetBlockPointer(&CacheManagerDrive, EndBlock);
        if (CacheBlock == NULL)
        {
            return FALSE;
        }

        //
        // Copy the portion requested into the buffer
        //
        RtlCopyMemory(Buffer,
            CacheBlock->BlockData,
            SectorOffsetInEndBlock * CacheManagerDrive.BytesPerSector);
        TRACE("3 - RtlCopyMemory(0x%x, 0x%x, %d)\n", Buffer, CacheBlock->BlockData, SectorOffsetInEndBlock * CacheManagerDrive.BytesPerSector);

        //
        // Update the buffer address
        //
        Buffer = (PVOID)((ULONG_PTR)Buffer + (SectorOffsetInEndBlock * CacheManagerDrive.BytesPerSector));

        //
        // Update the block count
        //
        BlockCount--;
    }

    return TRUE;
}