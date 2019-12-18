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
struct TYPE_5__ {scalar_t__ lastBlock; } ;
typedef  TYPE_1__ blockProperties_t ;
struct TYPE_6__ {scalar_t__ checksumFlag; scalar_t__ headerSize; } ;
typedef  TYPE_2__ ZSTD_frameHeader ;
typedef  void BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t MEM_readLE32 (void const*) ; 
 int ZSTD_FRAMEIDSIZE ; 
 int ZSTD_MAGIC_SKIPPABLE_START ; 
 size_t const ZSTD_blockHeaderSize ; 
 size_t ZSTD_findFrameCompressedSizeLegacy (void const*,size_t) ; 
 size_t ZSTD_getFrameHeader (TYPE_2__*,void const*,size_t) ; 
 size_t ZSTD_getcBlockSize (void const*,size_t,TYPE_1__*) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 scalar_t__ ZSTD_isLegacy (void const*,size_t) ; 
 size_t ZSTD_skippableHeaderSize ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZSTD_findFrameCompressedSize(const void *src, size_t srcSize)
{
#if defined(ZSTD_LEGACY_SUPPORT) && (ZSTD_LEGACY_SUPPORT >= 1)
    if (ZSTD_isLegacy(src, srcSize))
        return ZSTD_findFrameCompressedSizeLegacy(src, srcSize);
#endif
    if ( (srcSize >= ZSTD_skippableHeaderSize)
      && (MEM_readLE32(src) & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START ) {
        return ZSTD_skippableHeaderSize + MEM_readLE32((const BYTE*)src + ZSTD_FRAMEIDSIZE);
    } else {
        const BYTE* ip = (const BYTE*)src;
        const BYTE* const ipstart = ip;
        size_t remainingSize = srcSize;
        ZSTD_frameHeader zfh;

        /* Extract Frame Header */
        {   size_t const ret = ZSTD_getFrameHeader(&zfh, src, srcSize);
            if (ZSTD_isError(ret)) return ret;
            if (ret > 0) return ERROR(srcSize_wrong);
        }

        ip += zfh.headerSize;
        remainingSize -= zfh.headerSize;

        /* Loop on each block */
        while (1) {
            blockProperties_t blockProperties;
            size_t const cBlockSize = ZSTD_getcBlockSize(ip, remainingSize, &blockProperties);
            if (ZSTD_isError(cBlockSize)) return cBlockSize;

            if (ZSTD_blockHeaderSize + cBlockSize > remainingSize)
                return ERROR(srcSize_wrong);

            ip += ZSTD_blockHeaderSize + cBlockSize;
            remainingSize -= ZSTD_blockHeaderSize + cBlockSize;

            if (blockProperties.lastBlock) break;
        }

        if (zfh.checksumFlag) {   /* Final frame content checksum */
            if (remainingSize < 4) return ERROR(srcSize_wrong);
            ip += 4;
        }

        return ip - ipstart;
    }
}