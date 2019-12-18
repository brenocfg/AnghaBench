#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_17__ {scalar_t__ HighPart; } ;
struct TYPE_19__ {int QuadPart; TYPE_1__ u; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_18__ {int /*<<< orphan*/  storageDirEntry; } ;
struct TYPE_22__ {scalar_t__ firstFreeSmallBlock; int bigBlockSize; scalar_t__ smallBlockSize; TYPE_2__ base; int /*<<< orphan*/  smallBlockRootChain; int /*<<< orphan*/  smallBlockDepotChain; } ;
struct TYPE_21__ {TYPE_3__ size; } ;
struct TYPE_20__ {TYPE_6__* parentStorage; } ;
typedef  TYPE_4__ SmallBlockChainStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_5__ DirEntry ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 
 scalar_t__ BLOCK_UNUSED ; 
 int /*<<< orphan*/  BlockChainStream_Enlarge (int /*<<< orphan*/ ,TYPE_3__) ; 
 scalar_t__ BlockChainStream_GetCount (int /*<<< orphan*/ ) ; 
 TYPE_3__ BlockChainStream_GetSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BlockChainStream_ReadAt (int /*<<< orphan*/ ,TYPE_3__,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  BlockChainStream_SetSize (int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  BlockChainStream_WriteAt (int /*<<< orphan*/ ,TYPE_3__,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int MAX_BIG_BLOCK_SIZE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageImpl_ReadDirEntry (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  StorageImpl_SaveFileHeader (TYPE_6__*) ; 
 int /*<<< orphan*/  StorageImpl_WriteDirEntry (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  StorageUtl_ReadDWord (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static ULONG SmallBlockChainStream_GetNextFreeBlock(
  SmallBlockChainStream* This)
{
  ULARGE_INTEGER offsetOfBlockInDepot;
  DWORD buffer;
  ULONG bytesRead;
  ULONG blockIndex = This->parentStorage->firstFreeSmallBlock;
  ULONG nextBlockIndex = BLOCK_END_OF_CHAIN;
  HRESULT res = S_OK;
  ULONG smallBlocksPerBigBlock;
  DirEntry rootEntry;
  ULONG blocksRequired;
  ULARGE_INTEGER old_size, size_required;

  offsetOfBlockInDepot.u.HighPart = 0;

  /*
   * Scan the small block depot for a free block
   */
  while (nextBlockIndex != BLOCK_UNUSED)
  {
    offsetOfBlockInDepot.QuadPart = (ULONGLONG)blockIndex * sizeof(ULONG);

    res = BlockChainStream_ReadAt(
                This->parentStorage->smallBlockDepotChain,
                offsetOfBlockInDepot,
                sizeof(DWORD),
                &buffer,
                &bytesRead);

    /*
     * If we run out of space for the small block depot, enlarge it
     */
    if (SUCCEEDED(res) && bytesRead == sizeof(DWORD))
    {
      StorageUtl_ReadDWord((BYTE *)&buffer, 0, &nextBlockIndex);

      if (nextBlockIndex != BLOCK_UNUSED)
        blockIndex++;
    }
    else
    {
      ULONG count =
        BlockChainStream_GetCount(This->parentStorage->smallBlockDepotChain);

      BYTE smallBlockDepot[MAX_BIG_BLOCK_SIZE];
      ULARGE_INTEGER newSize, offset;
      ULONG bytesWritten;

      newSize.QuadPart = (ULONGLONG)(count + 1) * This->parentStorage->bigBlockSize;
      BlockChainStream_Enlarge(This->parentStorage->smallBlockDepotChain, newSize);

      /*
       * Initialize all the small blocks to free
       */
      memset(smallBlockDepot, BLOCK_UNUSED, This->parentStorage->bigBlockSize);
      offset.QuadPart = (ULONGLONG)count * This->parentStorage->bigBlockSize;
      BlockChainStream_WriteAt(This->parentStorage->smallBlockDepotChain,
        offset, This->parentStorage->bigBlockSize, smallBlockDepot, &bytesWritten);

      StorageImpl_SaveFileHeader(This->parentStorage);
    }
  }

  This->parentStorage->firstFreeSmallBlock = blockIndex+1;

  smallBlocksPerBigBlock =
    This->parentStorage->bigBlockSize / This->parentStorage->smallBlockSize;

  /*
   * Verify if we have to allocate big blocks to contain small blocks
   */
  blocksRequired = (blockIndex / smallBlocksPerBigBlock) + 1;

  size_required.QuadPart = (ULONGLONG)blocksRequired * This->parentStorage->bigBlockSize;

  old_size = BlockChainStream_GetSize(This->parentStorage->smallBlockRootChain);

  if (size_required.QuadPart > old_size.QuadPart)
  {
    BlockChainStream_SetSize(
      This->parentStorage->smallBlockRootChain,
      size_required);

    StorageImpl_ReadDirEntry(
      This->parentStorage,
      This->parentStorage->base.storageDirEntry,
      &rootEntry);

    rootEntry.size = size_required;

    StorageImpl_WriteDirEntry(
      This->parentStorage,
      This->parentStorage->base.storageDirEntry,
      &rootEntry);
  }

  return blockIndex;
}