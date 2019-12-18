#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_12__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_14__ {scalar_t__ QuadPart; TYPE_1__ u; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_15__ {TYPE_2__* parentStorage; } ;
struct TYPE_13__ {scalar_t__ smallBlockSize; int /*<<< orphan*/  smallBlockRootChain; } ;
typedef  TYPE_4__ SmallBlockChainStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 
 int /*<<< orphan*/  BlockChainStream_ReadAt (int /*<<< orphan*/ ,TYPE_3__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STG_E_DOCFILECORRUPT ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ SmallBlockChainStream_GetHeadOfChain (TYPE_4__*) ; 
 int /*<<< orphan*/  SmallBlockChainStream_GetNextBlockInChain (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 TYPE_3__ SmallBlockChainStream_GetSize (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

HRESULT SmallBlockChainStream_ReadAt(
  SmallBlockChainStream* This,
  ULARGE_INTEGER         offset,
  ULONG                  size,
  void*                  buffer,
  ULONG*                 bytesRead)
{
  HRESULT rc = S_OK;
  ULARGE_INTEGER offsetInBigBlockFile;
  ULONG blockNoInSequence =
    offset.u.LowPart / This->parentStorage->smallBlockSize;

  ULONG offsetInBlock = offset.u.LowPart % This->parentStorage->smallBlockSize;
  ULONG bytesToReadInBuffer;
  ULONG blockIndex;
  ULONG bytesReadFromBigBlockFile;
  BYTE* bufferWalker;
  ULARGE_INTEGER stream_size;

  /*
   * This should never happen on a small block file.
   */
  assert(offset.u.HighPart==0);

  *bytesRead   = 0;

  stream_size = SmallBlockChainStream_GetSize(This);
  if (stream_size.QuadPart > offset.QuadPart)
    size = min(stream_size.QuadPart - offset.QuadPart, size);
  else
    return S_OK;

  /*
   * Find the first block in the stream that contains part of the buffer.
   */
  blockIndex = SmallBlockChainStream_GetHeadOfChain(This);

  while ( (blockNoInSequence > 0) &&  (blockIndex != BLOCK_END_OF_CHAIN))
  {
    rc = SmallBlockChainStream_GetNextBlockInChain(This, blockIndex, &blockIndex);
    if(FAILED(rc))
      return rc;
    blockNoInSequence--;
  }

  /*
   * Start reading the buffer.
   */
  bufferWalker = buffer;

  while ( (size > 0) && (blockIndex != BLOCK_END_OF_CHAIN) )
  {
    /*
     * Calculate how many bytes we can copy from this small block.
     */
    bytesToReadInBuffer =
      min(This->parentStorage->smallBlockSize - offsetInBlock, size);

    /*
     * Calculate the offset of the small block in the small block file.
     */
    offsetInBigBlockFile.QuadPart   =
      (ULONGLONG)blockIndex * This->parentStorage->smallBlockSize;

    offsetInBigBlockFile.QuadPart  += offsetInBlock;

    /*
     * Read those bytes in the buffer from the small block file.
     * The small block has already been identified so it shouldn't fail
     * unless the file is corrupt.
     */
    rc = BlockChainStream_ReadAt(This->parentStorage->smallBlockRootChain,
      offsetInBigBlockFile,
      bytesToReadInBuffer,
      bufferWalker,
      &bytesReadFromBigBlockFile);

    if (FAILED(rc))
      return rc;

    if (!bytesReadFromBigBlockFile)
      return STG_E_DOCFILECORRUPT;

    /*
     * Step to the next big block.
     */
    rc = SmallBlockChainStream_GetNextBlockInChain(This, blockIndex, &blockIndex);
    if(FAILED(rc))
      return STG_E_DOCFILECORRUPT;

    bufferWalker += bytesReadFromBigBlockFile;
    size         -= bytesReadFromBigBlockFile;
    *bytesRead   += bytesReadFromBigBlockFile;
    offsetInBlock = (offsetInBlock + bytesReadFromBigBlockFile) % This->parentStorage->smallBlockSize;
  }

  return S_OK;
}