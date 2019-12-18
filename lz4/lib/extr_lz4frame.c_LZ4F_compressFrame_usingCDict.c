#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prefs ;
typedef  int /*<<< orphan*/  options ;
typedef  scalar_t__ U64 ;
struct TYPE_10__ {scalar_t__ contentSize; int /*<<< orphan*/  blockMode; int /*<<< orphan*/  blockSizeID; } ;
struct TYPE_11__ {int autoFlush; int stableSrc; TYPE_1__ frameInfo; } ;
typedef  TYPE_2__ LZ4F_preferences_t ;
typedef  TYPE_2__ LZ4F_compressOptions_t ;
typedef  int /*<<< orphan*/  LZ4F_cctx ;
typedef  int /*<<< orphan*/  LZ4F_CDict ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4F_ERROR_dstMaxSize_tooSmall ; 
 int /*<<< orphan*/  LZ4F_blockIndependent ; 
 size_t LZ4F_compressBegin_usingCDict (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 size_t LZ4F_compressEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,TYPE_2__*) ; 
 size_t LZ4F_compressFrameBound (size_t,TYPE_2__*) ; 
 size_t LZ4F_compressUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,void const*,size_t,TYPE_2__*) ; 
 size_t LZ4F_getBlockSize (int /*<<< orphan*/ ) ; 
 scalar_t__ LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  LZ4F_optimalBSID (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MEM_INIT (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t err0r (int /*<<< orphan*/ ) ; 

size_t LZ4F_compressFrame_usingCDict(LZ4F_cctx* cctx,
                                     void* dstBuffer, size_t dstCapacity,
                               const void* srcBuffer, size_t srcSize,
                               const LZ4F_CDict* cdict,
                               const LZ4F_preferences_t* preferencesPtr)
{
    LZ4F_preferences_t prefs;
    LZ4F_compressOptions_t options;
    BYTE* const dstStart = (BYTE*) dstBuffer;
    BYTE* dstPtr = dstStart;
    BYTE* const dstEnd = dstStart + dstCapacity;

    if (preferencesPtr!=NULL)
        prefs = *preferencesPtr;
    else
        MEM_INIT(&prefs, 0, sizeof(prefs));
    if (prefs.frameInfo.contentSize != 0)
        prefs.frameInfo.contentSize = (U64)srcSize;   /* auto-correct content size if selected (!=0) */

    prefs.frameInfo.blockSizeID = LZ4F_optimalBSID(prefs.frameInfo.blockSizeID, srcSize);
    prefs.autoFlush = 1;
    if (srcSize <= LZ4F_getBlockSize(prefs.frameInfo.blockSizeID))
        prefs.frameInfo.blockMode = LZ4F_blockIndependent;   /* only one block => no need for inter-block link */

    MEM_INIT(&options, 0, sizeof(options));
    options.stableSrc = 1;

    if (dstCapacity < LZ4F_compressFrameBound(srcSize, &prefs))  /* condition to guarantee success */
        return err0r(LZ4F_ERROR_dstMaxSize_tooSmall);

    { size_t const headerSize = LZ4F_compressBegin_usingCDict(cctx, dstBuffer, dstCapacity, cdict, &prefs);  /* write header */
      if (LZ4F_isError(headerSize)) return headerSize;
      dstPtr += headerSize;   /* header size */ }

    assert(dstEnd >= dstPtr);
    { size_t const cSize = LZ4F_compressUpdate(cctx, dstPtr, (size_t)(dstEnd-dstPtr), srcBuffer, srcSize, &options);
      if (LZ4F_isError(cSize)) return cSize;
      dstPtr += cSize; }

    assert(dstEnd >= dstPtr);
    { size_t const tailSize = LZ4F_compressEnd(cctx, dstPtr, (size_t)(dstEnd-dstPtr), &options);   /* flush last block, and generate suffix */
      if (LZ4F_isError(tailSize)) return tailSize;
      dstPtr += tailSize; }

    assert(dstEnd >= dstStart);
    return (size_t)(dstPtr - dstStart);
}