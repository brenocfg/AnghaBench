#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_15__ {scalar_t__ LowPart; } ;
struct TYPE_16__ {TYPE_1__ u; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_19__ {scalar_t__ smallBlockSize; } ;
struct TYPE_18__ {scalar_t__ startingBlock; } ;
struct TYPE_17__ {TYPE_5__* parentStorage; int /*<<< orphan*/  ownerDirEntry; scalar_t__* headOfStreamPlaceHolder; } ;
typedef  TYPE_3__ SmallBlockChainStream ;
typedef  TYPE_4__ DirEntry ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SmallBlockChainStream_GetHeadOfChain (TYPE_3__*) ; 
 int /*<<< orphan*/  SmallBlockChainStream_GetNextBlockInChain (TYPE_3__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ SmallBlockChainStream_GetNextFreeBlock (TYPE_3__*) ; 
 int /*<<< orphan*/  SmallBlockChainStream_SetNextBlockInChain (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  StorageImpl_ReadDirEntry (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  StorageImpl_WriteDirEntry (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL SmallBlockChainStream_Enlarge(
  SmallBlockChainStream* This,
  ULARGE_INTEGER newSize)
{
  ULONG blockIndex, currentBlock;
  ULONG newNumBlocks;
  ULONG oldNumBlocks = 0;

  blockIndex = SmallBlockChainStream_GetHeadOfChain(This);

  /*
   * Empty chain. Create the head.
   */
  if (blockIndex == BLOCK_END_OF_CHAIN)
  {
    blockIndex = SmallBlockChainStream_GetNextFreeBlock(This);
    SmallBlockChainStream_SetNextBlockInChain(
        This,
        blockIndex,
        BLOCK_END_OF_CHAIN);

    if (This->headOfStreamPlaceHolder != NULL)
    {
      *(This->headOfStreamPlaceHolder) = blockIndex;
    }
    else
    {
      DirEntry chainEntry;

      StorageImpl_ReadDirEntry(This->parentStorage, This->ownerDirEntry,
                                   &chainEntry);

      chainEntry.startingBlock = blockIndex;

      StorageImpl_WriteDirEntry(This->parentStorage, This->ownerDirEntry,
                                  &chainEntry);
    }
  }

  currentBlock = blockIndex;

  /*
   * Figure out how many blocks are needed to contain this stream
   */
  newNumBlocks = newSize.u.LowPart / This->parentStorage->smallBlockSize;

  if ((newSize.u.LowPart % This->parentStorage->smallBlockSize) != 0)
    newNumBlocks++;

  /*
   * Go to the current end of chain
   */
  while (blockIndex != BLOCK_END_OF_CHAIN)
  {
    oldNumBlocks++;
    currentBlock = blockIndex;
    if(FAILED(SmallBlockChainStream_GetNextBlockInChain(This, currentBlock, &blockIndex)))
      return FALSE;
  }

  /*
   * Add new blocks to the chain
   */
  while (oldNumBlocks < newNumBlocks)
  {
    blockIndex = SmallBlockChainStream_GetNextFreeBlock(This);
    SmallBlockChainStream_SetNextBlockInChain(This, currentBlock, blockIndex);

    SmallBlockChainStream_SetNextBlockInChain(
      This,
      blockIndex,
      BLOCK_END_OF_CHAIN);

    currentBlock = blockIndex;
    oldNumBlocks++;
  }

  return TRUE;
}