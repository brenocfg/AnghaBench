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
struct TYPE_5__ {size_t dstBufferSize; scalar_t__ srcBuffer; int /*<<< orphan*/  dstBuffer; int /*<<< orphan*/  ctx; int /*<<< orphan*/  srcBufferSize; } ;
typedef  TYPE_1__ cRess_t ;
struct TYPE_6__ {unsigned int blockSizeID; } ;
typedef  TYPE_2__ LZ4F_frameInfo_t ;
typedef  size_t LZ4F_errorCode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
 size_t LZ4F_decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,char*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_getErrorName (size_t) ; 
 size_t LZ4F_getFrameInfo (int /*<<< orphan*/ ,TYPE_2__*,char*,size_t*) ; 
 scalar_t__ LZ4F_isError (size_t) ; 
 scalar_t__ ferror (int /*<<< orphan*/ * const) ; 
 size_t fread (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 

int frameCheck(cRess_t ress, FILE* const srcFile, unsigned bsid, size_t blockSize)
{
    LZ4F_errorCode_t nextToLoad = 0;
    size_t curblocksize = 0;
    int partialBlock = 0;

    /* Main Loop */
    for (;;) {
        size_t readSize;
        size_t pos = 0;
        size_t decodedBytes = ress.dstBufferSize;
        size_t remaining;
        LZ4F_frameInfo_t frameInfo;

        /* Read input */
        readSize = fread(ress.srcBuffer, 1, ress.srcBufferSize, srcFile);
        if (!readSize) break;   /* reached end of file or stream */

        while (pos < readSize) {  /* still to read */
            /* Decode Input (at least partially) */
            if (!nextToLoad) {
                /* LZ4F_decompress returned 0 : starting new frame */
                curblocksize = 0;
                remaining = readSize - pos;
                nextToLoad = LZ4F_getFrameInfo(ress.ctx, &frameInfo, (char*)(ress.srcBuffer)+pos, &remaining);
                if (LZ4F_isError(nextToLoad))
                    EXM_THROW(22, "Error getting frame info: %s",
                                LZ4F_getErrorName(nextToLoad));
                if (frameInfo.blockSizeID != bsid)
                    EXM_THROW(23, "Block size ID %u != expected %u",
                                frameInfo.blockSizeID, bsid);
                pos += remaining;
                /* nextToLoad should be block header size */
                remaining = nextToLoad;
                decodedBytes = ress.dstBufferSize;
                nextToLoad = LZ4F_decompress(ress.ctx, ress.dstBuffer, &decodedBytes, (char*)(ress.srcBuffer)+pos, &remaining, NULL);
                if (LZ4F_isError(nextToLoad)) EXM_THROW(24, "Decompression error : %s", LZ4F_getErrorName(nextToLoad));
                pos += remaining;
            }
            decodedBytes = ress.dstBufferSize;
            /* nextToLoad should be just enough to cover the next block */
            if (nextToLoad > (readSize - pos)) {
                /* block is not fully contained in current buffer */
                partialBlock = 1;
                remaining = readSize - pos;
            } else {
                if (partialBlock) {
                    partialBlock = 0;
                }
                remaining = nextToLoad;
            }
            nextToLoad = LZ4F_decompress(ress.ctx, ress.dstBuffer, &decodedBytes, (char*)(ress.srcBuffer)+pos, &remaining, NULL);
            if (LZ4F_isError(nextToLoad)) EXM_THROW(24, "Decompression error : %s", LZ4F_getErrorName(nextToLoad));
            curblocksize += decodedBytes;
            pos += remaining;
            if (!partialBlock) {
                /* detect small block due to end of frame; the final 4-byte frame checksum could be left in the buffer */
                if ((curblocksize != 0) && (nextToLoad > 4)) {
                    if (curblocksize != blockSize)
                        EXM_THROW(25, "Block size %u != expected %u, pos %u\n",
                                    (unsigned)curblocksize, (unsigned)blockSize, (unsigned)pos);
                }
                curblocksize = 0;
            }
        }
    }
    /* can be out because readSize == 0, which could be an fread() error */
    if (ferror(srcFile)) EXM_THROW(26, "Read error");

    if (nextToLoad!=0) EXM_THROW(27, "Unfinished stream");

    return 0;
}