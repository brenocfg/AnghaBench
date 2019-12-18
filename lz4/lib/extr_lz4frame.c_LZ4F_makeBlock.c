#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ (* compressFunc_t ) (void*,char const*,char*,int,int,int,int /*<<< orphan*/  const*) ;
typedef  int U32 ;
typedef  scalar_t__ LZ4F_blockChecksum_t ;
typedef  int /*<<< orphan*/  LZ4F_CDict ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int BFSize ; 
 int BHSize ; 
 int LZ4F_BLOCKUNCOMPRESSED_FLAG ; 
 int /*<<< orphan*/  LZ4F_writeLE32 (int /*<<< orphan*/ * const,int const) ; 
 int XXH32 (int /*<<< orphan*/ * const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ * const,void const*,size_t) ; 

__attribute__((used)) static size_t LZ4F_makeBlock(void* dst,
                       const void* src, size_t srcSize,
                             compressFunc_t compress, void* lz4ctx, int level,
                       const LZ4F_CDict* cdict,
                             LZ4F_blockChecksum_t crcFlag)
{
    BYTE* const cSizePtr = (BYTE*)dst;
    U32 cSize = (U32)compress(lz4ctx, (const char*)src, (char*)(cSizePtr+BHSize),
                                      (int)(srcSize), (int)(srcSize-1),
                                      level, cdict);
    if (cSize == 0) {  /* compression failed */
        cSize = (U32)srcSize;
        LZ4F_writeLE32(cSizePtr, cSize | LZ4F_BLOCKUNCOMPRESSED_FLAG);
        memcpy(cSizePtr+BHSize, src, srcSize);
    } else {
        LZ4F_writeLE32(cSizePtr, cSize);
    }
    if (crcFlag) {
        U32 const crc32 = XXH32(cSizePtr+BHSize, cSize, 0);  /* checksum of compressed data */
        LZ4F_writeLE32(cSizePtr+BHSize+cSize, crc32);
    }
    return BHSize + cSize + ((U32)crcFlag)*BFSize;
}