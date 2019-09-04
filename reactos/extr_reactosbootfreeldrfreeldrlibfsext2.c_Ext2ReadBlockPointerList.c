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
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_5__ {int* dir_blocks; int /*<<< orphan*/  tripple_indir_block; int /*<<< orphan*/  double_indir_block; int /*<<< orphan*/  indir_block; } ;
struct TYPE_6__ {TYPE_1__ blocks; } ;
typedef  TYPE_2__* PEXT2_INODE ;

/* Variables and functions */
 int Ext2BlockSizeInBytes ; 
 int /*<<< orphan*/  Ext2CopyDoubleIndirectBlockPointers (int*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2CopyIndirectBlockPointers (int*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2CopyTripleIndirectBlockPointers (int*,int*,int,int /*<<< orphan*/ ) ; 
 int Ext2GetInodeFileSize (TYPE_2__*) ; 
 int* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int*,int /*<<< orphan*/ ) ; 
 int INDIRECT_BLOCKS ; 
 int ROUND_UP (int,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int*,int) ; 
 int /*<<< orphan*/  TAG_EXT_BLOCK_LIST ; 
 int /*<<< orphan*/  TRACE (char*) ; 

ULONG* Ext2ReadBlockPointerList(PEXT2_INODE Inode)
{
    ULONGLONG        FileSize;
    ULONG        BlockCount;
    ULONG*    BlockList;
    ULONG        CurrentBlockInList;
    ULONG        CurrentBlock;

    TRACE("Ext2ReadBlockPointerList()\n");

    // Get the number of blocks this file occupies
    // I would just use Inode->i_blocks but it
    // doesn't seem to be the number of blocks
    // the file size corresponds to, but instead
    // it is much bigger.
    //BlockCount = Inode->i_blocks;
    FileSize = Ext2GetInodeFileSize(Inode);
    FileSize = ROUND_UP(FileSize, Ext2BlockSizeInBytes);
    BlockCount = (ULONG)(FileSize / Ext2BlockSizeInBytes);

    // Allocate the memory for the block list
    BlockList = FrLdrTempAlloc(BlockCount * sizeof(ULONG), TAG_EXT_BLOCK_LIST);
    if (BlockList == NULL)
    {
        return NULL;
    }

    RtlZeroMemory(BlockList, BlockCount * sizeof(ULONG));

    // Copy the direct block pointers
    for (CurrentBlockInList = CurrentBlock = 0;
         CurrentBlockInList < BlockCount && CurrentBlock < INDIRECT_BLOCKS;
         CurrentBlock++, CurrentBlockInList++)
    {
        BlockList[CurrentBlockInList] = Inode->blocks.dir_blocks[CurrentBlock];
    }

    // Copy the indirect block pointers
    if (CurrentBlockInList < BlockCount)
    {
        if (!Ext2CopyIndirectBlockPointers(BlockList, &CurrentBlockInList, BlockCount, Inode->blocks.indir_block))
        {
            FrLdrTempFree(BlockList, TAG_EXT_BLOCK_LIST);
            return NULL;
        }
    }

    // Copy the double indirect block pointers
    if (CurrentBlockInList < BlockCount)
    {
        if (!Ext2CopyDoubleIndirectBlockPointers(BlockList, &CurrentBlockInList, BlockCount, Inode->blocks.double_indir_block))
        {
            FrLdrTempFree(BlockList, TAG_EXT_BLOCK_LIST);
            return NULL;
        }
    }

    // Copy the triple indirect block pointers
    if (CurrentBlockInList < BlockCount)
    {
        if (!Ext2CopyTripleIndirectBlockPointers(BlockList, &CurrentBlockInList, BlockCount, Inode->blocks.tripple_indir_block))
        {
            FrLdrTempFree(BlockList, TAG_EXT_BLOCK_LIST);
            return NULL;
        }
    }

    return BlockList;
}