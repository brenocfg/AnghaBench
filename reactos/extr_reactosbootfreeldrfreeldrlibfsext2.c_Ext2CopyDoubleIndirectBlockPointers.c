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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int Ext2BlockSizeInBytes ; 
 int /*<<< orphan*/  Ext2CopyIndirectBlockPointers (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Ext2ReadBlock (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_EXT_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2CopyDoubleIndirectBlockPointers(ULONG* BlockList, ULONG* CurrentBlockInList, ULONG BlockCount, ULONG DoubleIndirectBlock)
{
    ULONG*    BlockBuffer;
    ULONG    CurrentBlock;
    ULONG    BlockPointersPerBlock;

    TRACE("Ext2CopyDoubleIndirectBlockPointers() BlockCount = %d\n", BlockCount);

    BlockPointersPerBlock = Ext2BlockSizeInBytes / sizeof(ULONG);

    BlockBuffer = (ULONG*)FrLdrTempAlloc(Ext2BlockSizeInBytes, TAG_EXT_BUFFER);
    if (BlockBuffer == NULL)
    {
        return FALSE;
    }

    if (!Ext2ReadBlock(DoubleIndirectBlock, BlockBuffer))
    {
        FrLdrTempFree(BlockBuffer, TAG_EXT_BUFFER);
        return FALSE;
    }

    for (CurrentBlock=0; (*CurrentBlockInList)<BlockCount && CurrentBlock<BlockPointersPerBlock; CurrentBlock++)
    {
        if (!Ext2CopyIndirectBlockPointers(BlockList, CurrentBlockInList, BlockCount, BlockBuffer[CurrentBlock]))
        {
            FrLdrTempFree(BlockBuffer, TAG_EXT_BUFFER);
            return FALSE;
        }
    }

    FrLdrTempFree(BlockBuffer, TAG_EXT_BUFFER);
    return TRUE;
}