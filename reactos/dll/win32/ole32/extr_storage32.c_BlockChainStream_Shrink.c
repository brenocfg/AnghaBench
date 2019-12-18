#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct BlockChainRun {int lastOffset; scalar_t__ firstSector; scalar_t__ firstOffset; } ;
typedef  int ULONG ;
struct TYPE_15__ {int QuadPart; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_18__ {int bigBlockSize; } ;
struct TYPE_17__ {int tailIndex; scalar_t__ ownerDirEntry; int numBlocks; int indexCacheLen; TYPE_1__* cachedBlocks; TYPE_5__* parentStorage; struct BlockChainRun* indexCache; void** headOfStreamPlaceHolder; } ;
struct TYPE_16__ {void* startingBlock; } ;
struct TYPE_14__ {int index; int /*<<< orphan*/  dirty; } ;
typedef  TYPE_3__ DirEntry ;
typedef  TYPE_4__ BlockChainStream ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* BLOCK_END_OF_CHAIN ; 
 int BlockChainStream_GetSectorOfOffset (TYPE_4__*,int) ; 
 scalar_t__ DIRENTRY_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  StorageImpl_FreeBigBlock (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  StorageImpl_ReadDirEntry (TYPE_5__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  StorageImpl_SetNextBlockInChain (TYPE_5__*,int,void*) ; 
 int /*<<< orphan*/  StorageImpl_WriteDirEntry (TYPE_5__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static BOOL BlockChainStream_Shrink(BlockChainStream* This,
                                    ULARGE_INTEGER    newSize)
{
  ULONG blockIndex;
  ULONG numBlocks;
  int i;

  /*
   * Figure out how many blocks are needed to contain the new size
   */
  numBlocks = newSize.QuadPart / This->parentStorage->bigBlockSize;

  if ((newSize.QuadPart % This->parentStorage->bigBlockSize) != 0)
    numBlocks++;

  if (numBlocks)
  {
    /*
     * Go to the new end of chain
     */
    blockIndex = BlockChainStream_GetSectorOfOffset(This, numBlocks-1);

    /* Mark the new end of chain */
    StorageImpl_SetNextBlockInChain(
      This->parentStorage,
      blockIndex,
      BLOCK_END_OF_CHAIN);

    This->tailIndex = blockIndex;
  }
  else
  {
    if (This->headOfStreamPlaceHolder != 0)
    {
      *This->headOfStreamPlaceHolder = BLOCK_END_OF_CHAIN;
    }
    else
    {
      DirEntry chainEntry;
      assert(This->ownerDirEntry != DIRENTRY_NULL);

      StorageImpl_ReadDirEntry(
        This->parentStorage,
        This->ownerDirEntry,
        &chainEntry);

      chainEntry.startingBlock = BLOCK_END_OF_CHAIN;

      StorageImpl_WriteDirEntry(
        This->parentStorage,
        This->ownerDirEntry,
        &chainEntry);
    }

    This->tailIndex = BLOCK_END_OF_CHAIN;
  }

  This->numBlocks = numBlocks;

  /*
   * Mark the extra blocks as free
   */
  while (This->indexCacheLen && This->indexCache[This->indexCacheLen-1].lastOffset >= numBlocks)
  {
    struct BlockChainRun *last_run = &This->indexCache[This->indexCacheLen-1];
    StorageImpl_FreeBigBlock(This->parentStorage,
      last_run->firstSector + last_run->lastOffset - last_run->firstOffset);
    if (last_run->lastOffset == last_run->firstOffset)
      This->indexCacheLen--;
    else
      last_run->lastOffset--;
  }

  /*
   * Reset the last accessed block cache.
   */
  for (i=0; i<2; i++)
  {
    if (This->cachedBlocks[i].index >= numBlocks)
    {
      This->cachedBlocks[i].index = 0xffffffff;
      This->cachedBlocks[i].dirty = FALSE;
    }
  }

  return TRUE;
}