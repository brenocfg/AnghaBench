#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ frameType; unsigned long long frameContentSize; } ;
typedef  TYPE_1__ ZSTD_frameHeader ;

/* Variables and functions */
 unsigned long long ZSTD_CONTENTSIZE_ERROR ; 
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 unsigned long long ZSTD_getDecompressedSize_legacy (void const*,size_t) ; 
 scalar_t__ ZSTD_getFrameHeader (TYPE_1__*,void const*,size_t) ; 
 scalar_t__ ZSTD_isLegacy (void const*,size_t) ; 
 scalar_t__ ZSTD_skippableFrame ; 

unsigned long long ZSTD_getFrameContentSize(const void *src, size_t srcSize)
{
#if defined(ZSTD_LEGACY_SUPPORT) && (ZSTD_LEGACY_SUPPORT >= 1)
    if (ZSTD_isLegacy(src, srcSize)) {
        unsigned long long const ret = ZSTD_getDecompressedSize_legacy(src, srcSize);
        return ret == 0 ? ZSTD_CONTENTSIZE_UNKNOWN : ret;
    }
#endif
    {   ZSTD_frameHeader zfh;
        if (ZSTD_getFrameHeader(&zfh, src, srcSize) != 0)
            return ZSTD_CONTENTSIZE_ERROR;
        if (zfh.frameType == ZSTD_skippableFrame) {
            return 0;
        } else {
            return zfh.frameContentSize;
    }   }
}