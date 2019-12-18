#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_5__ {int dictID; int /*<<< orphan*/  contentSize; int /*<<< orphan*/  blockSizeID; int /*<<< orphan*/  contentChecksumFlag; int /*<<< orphan*/  blockChecksumFlag; int /*<<< orphan*/  blockMode; int /*<<< orphan*/  frameType; } ;
struct TYPE_4__ {scalar_t__ const* header; size_t tmpInSize; int tmpInTarget; int /*<<< orphan*/  dStage; TYPE_2__ frameInfo; int /*<<< orphan*/  frameRemainingSize; int /*<<< orphan*/  maxBlockSize; } ;
typedef  TYPE_1__ LZ4F_dctx ;
typedef  int /*<<< orphan*/  LZ4F_contentChecksum_t ;
typedef  int /*<<< orphan*/  LZ4F_blockSizeID_t ;
typedef  int /*<<< orphan*/  LZ4F_blockMode_t ;
typedef  int /*<<< orphan*/  LZ4F_blockChecksum_t ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4F_ERROR_frameHeader_incomplete ; 
 int /*<<< orphan*/  LZ4F_ERROR_frameType_unknown ; 
 int /*<<< orphan*/  LZ4F_ERROR_headerChecksum_invalid ; 
 int /*<<< orphan*/  LZ4F_ERROR_headerVersion_wrong ; 
 int /*<<< orphan*/  LZ4F_ERROR_maxBlockSize_invalid ; 
 int /*<<< orphan*/  LZ4F_ERROR_reservedFlag_set ; 
 int LZ4F_MAGICNUMBER ; 
 int LZ4F_MAGIC_SKIPPABLE_START ; 
 int /*<<< orphan*/  LZ4F_frame ; 
 int /*<<< orphan*/  LZ4F_getBlockSize (unsigned int) ; 
 scalar_t__ LZ4F_headerChecksum (scalar_t__ const*,size_t) ; 
 int LZ4F_readLE32 (scalar_t__ const*) ; 
 int /*<<< orphan*/  LZ4F_readLE64 (scalar_t__ const*) ; 
 int /*<<< orphan*/  LZ4F_skippableFrame ; 
 int /*<<< orphan*/  MEM_INIT (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int const _1BIT ; 
 int const _2BITS ; 
 int const _3BITS ; 
 int const _4BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dstage_getSFrameSize ; 
 int /*<<< orphan*/  dstage_init ; 
 int /*<<< orphan*/  dstage_storeFrameHeader ; 
 int /*<<< orphan*/  dstage_storeSFrameSize ; 
 size_t err0r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__ const*,scalar_t__ const*,size_t) ; 
 size_t minFHSize ; 

__attribute__((used)) static size_t LZ4F_decodeHeader(LZ4F_dctx* dctx, const void* src, size_t srcSize)
{
    unsigned blockMode, blockChecksumFlag, contentSizeFlag, contentChecksumFlag, dictIDFlag, blockSizeID;
    size_t frameHeaderSize;
    const BYTE* srcPtr = (const BYTE*)src;

    /* need to decode header to get frameInfo */
    if (srcSize < minFHSize) return err0r(LZ4F_ERROR_frameHeader_incomplete);   /* minimal frame header size */
    MEM_INIT(&(dctx->frameInfo), 0, sizeof(dctx->frameInfo));

    /* special case : skippable frames */
    if ((LZ4F_readLE32(srcPtr) & 0xFFFFFFF0U) == LZ4F_MAGIC_SKIPPABLE_START) {
        dctx->frameInfo.frameType = LZ4F_skippableFrame;
        if (src == (void*)(dctx->header)) {
            dctx->tmpInSize = srcSize;
            dctx->tmpInTarget = 8;
            dctx->dStage = dstage_storeSFrameSize;
            return srcSize;
        } else {
            dctx->dStage = dstage_getSFrameSize;
            return 4;
        }
    }

    /* control magic number */
#ifndef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
    if (LZ4F_readLE32(srcPtr) != LZ4F_MAGICNUMBER)
        return err0r(LZ4F_ERROR_frameType_unknown);
#endif
    dctx->frameInfo.frameType = LZ4F_frame;

    /* Flags */
    {   U32 const FLG = srcPtr[4];
        U32 const version = (FLG>>6) & _2BITS;
        blockChecksumFlag = (FLG>>4) & _1BIT;
        blockMode = (FLG>>5) & _1BIT;
        contentSizeFlag = (FLG>>3) & _1BIT;
        contentChecksumFlag = (FLG>>2) & _1BIT;
        dictIDFlag = FLG & _1BIT;
        /* validate */
        if (((FLG>>1)&_1BIT) != 0) return err0r(LZ4F_ERROR_reservedFlag_set); /* Reserved bit */
        if (version != 1) return err0r(LZ4F_ERROR_headerVersion_wrong);        /* Version Number, only supported value */
    }

    /* Frame Header Size */
    frameHeaderSize = minFHSize + (contentSizeFlag?8:0) + (dictIDFlag?4:0);

    if (srcSize < frameHeaderSize) {
        /* not enough input to fully decode frame header */
        if (srcPtr != dctx->header)
            memcpy(dctx->header, srcPtr, srcSize);
        dctx->tmpInSize = srcSize;
        dctx->tmpInTarget = frameHeaderSize;
        dctx->dStage = dstage_storeFrameHeader;
        return srcSize;
    }

    {   U32 const BD = srcPtr[5];
        blockSizeID = (BD>>4) & _3BITS;
        /* validate */
        if (((BD>>7)&_1BIT) != 0) return err0r(LZ4F_ERROR_reservedFlag_set);   /* Reserved bit */
        if (blockSizeID < 4) return err0r(LZ4F_ERROR_maxBlockSize_invalid);    /* 4-7 only supported values for the time being */
        if (((BD>>0)&_4BITS) != 0) return err0r(LZ4F_ERROR_reservedFlag_set);  /* Reserved bits */
    }

    /* check header */
    assert(frameHeaderSize > 5);
#ifndef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
    {   BYTE const HC = LZ4F_headerChecksum(srcPtr+4, frameHeaderSize-5);
        if (HC != srcPtr[frameHeaderSize-1])
            return err0r(LZ4F_ERROR_headerChecksum_invalid);
    }
#endif

    /* save */
    dctx->frameInfo.blockMode = (LZ4F_blockMode_t)blockMode;
    dctx->frameInfo.blockChecksumFlag = (LZ4F_blockChecksum_t)blockChecksumFlag;
    dctx->frameInfo.contentChecksumFlag = (LZ4F_contentChecksum_t)contentChecksumFlag;
    dctx->frameInfo.blockSizeID = (LZ4F_blockSizeID_t)blockSizeID;
    dctx->maxBlockSize = LZ4F_getBlockSize(blockSizeID);
    if (contentSizeFlag)
        dctx->frameRemainingSize =
            dctx->frameInfo.contentSize = LZ4F_readLE64(srcPtr+6);
    if (dictIDFlag)
        dctx->frameInfo.dictID = LZ4F_readLE32(srcPtr + frameHeaderSize - 5);

    dctx->dStage = dstage_init;

    return frameHeaderSize;
}