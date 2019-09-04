#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int Ext2BlockSizeInBytes ; 
 int /*<<< orphan*/  Ext2ReadBlock (size_t,size_t*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_EXT_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2CopyIndirectBlockPointers(ULONG* BlockList, ULONG* CurrentBlockInList, ULONG BlockCount, ULONG IndirectBlock)
{
    ULONG*    BlockBuffer;
    ULONG    CurrentBlock;
    ULONG    BlockPointersPerBlock;

    TRACE("Ext2CopyIndirectBlockPointers() BlockCount = %d\n", BlockCount);

    BlockPointersPerBlock = Ext2BlockSizeInBytes / sizeof(ULONG);

    BlockBuffer = FrLdrTempAlloc(Ext2BlockSizeInBytes, TAG_EXT_BUFFER);
    if (!BlockBuffer)
    {
        return FALSE;
    }

    if (!Ext2ReadBlock(IndirectBlock, BlockBuffer))
    {
        return FALSE;
    }

    for (CurrentBlock=0; (*CurrentBlockInList)<BlockCount && CurrentBlock<BlockPointersPerBlock; CurrentBlock++)
    {
        BlockList[(*CurrentBlockInList)] = BlockBuffer[CurrentBlock];
        (*CurrentBlockInList)++;
    }

    FrLdrTempFree(BlockBuffer, TAG_EXT_BUFFER);

    return TRUE;
}