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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int const LEGACY_MAGICNUMBER ; 
 unsigned int const LZ4IO_MAGICNUMBER ; 
 int /*<<< orphan*/  LZ4IO_STATIC_ASSERT (int) ; 
 scalar_t__ LZ4IO_isSkippableMagicNumber (unsigned int const) ; 
 unsigned int LZ4IO_readLE32 (unsigned char**) ; 
 int LZIO_LEGACY_BLOCK_HEADER_SIZE ; 
 int MAGICNUMBER_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ UTIL_fseek (int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ ) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long long LZ4IO_skipLegacyBlocksData(FILE* finput) {
    unsigned char blockInfo[LZIO_LEGACY_BLOCK_HEADER_SIZE];
    unsigned long long totalBlocksSize = 0;
    LZ4IO_STATIC_ASSERT(LZIO_LEGACY_BLOCK_HEADER_SIZE == MAGICNUMBER_SIZE);
    for (;;) {
        if (!fread(blockInfo, 1, LZIO_LEGACY_BLOCK_HEADER_SIZE, finput)) {
            if (feof(finput)) return totalBlocksSize;
            return 0;
        }
        {   const unsigned int nextCBlockSize = LZ4IO_readLE32(&blockInfo);
            if ( nextCBlockSize == LEGACY_MAGICNUMBER ||
                    nextCBlockSize == LZ4IO_MAGICNUMBER ||
                    LZ4IO_isSkippableMagicNumber(nextCBlockSize)) {
                /* Rewind back. we want cursor at the begining of next frame.*/
                if (fseek(finput, -LZIO_LEGACY_BLOCK_HEADER_SIZE, SEEK_CUR) != 0) {
                    return 0;
                }
                break;
            }
            totalBlocksSize += LZIO_LEGACY_BLOCK_HEADER_SIZE + nextCBlockSize;
            /* skip to the next block */
            if (UTIL_fseek(finput, nextCBlockSize, SEEK_CUR) != 0) {
                return 0;
            }
        }
    }
    return totalBlocksSize;
}