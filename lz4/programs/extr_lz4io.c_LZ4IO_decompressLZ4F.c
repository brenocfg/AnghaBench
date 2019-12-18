#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* srcBuffer; size_t dstBufferSize; scalar_t__ srcBufferSize; int /*<<< orphan*/  dstBuffer; int /*<<< orphan*/  dictBufferSize; int /*<<< orphan*/  dictBuffer; int /*<<< orphan*/  dCtx; } ;
typedef  TYPE_1__ dRess_t ;
struct TYPE_7__ {int /*<<< orphan*/  testMode; } ;
typedef  TYPE_2__ LZ4IO_prefs_t ;
typedef  scalar_t__ LZ4F_errorCode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYUPDATE (int,char*,unsigned int) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
 scalar_t__ LZ4F_decompress_usingDict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_getErrorName (scalar_t__) ; 
 scalar_t__ LZ4F_isError (scalar_t__) ; 
 int /*<<< orphan*/  LZ4IO_MAGICNUMBER ; 
 unsigned int LZ4IO_fwriteSparse (TYPE_2__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 int /*<<< orphan*/  LZ4IO_fwriteSparseEnd (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  LZ4IO_writeLE32 (char*,int /*<<< orphan*/ ) ; 
 size_t MAGICNUMBER_SIZE ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long long LZ4IO_decompressLZ4F(LZ4IO_prefs_t* const prefs, dRess_t ress, FILE* srcFile, FILE* dstFile)
{
    unsigned long long filesize = 0;
    LZ4F_errorCode_t nextToLoad;
    unsigned storedSkips = 0;

    /* Init feed with magic number (already consumed from FILE* sFile) */
    {   size_t inSize = MAGICNUMBER_SIZE;
        size_t outSize= 0;
        LZ4IO_writeLE32(ress.srcBuffer, LZ4IO_MAGICNUMBER);
        nextToLoad = LZ4F_decompress_usingDict(ress.dCtx, ress.dstBuffer, &outSize, ress.srcBuffer, &inSize, ress.dictBuffer, ress.dictBufferSize, NULL);
        if (LZ4F_isError(nextToLoad)) EXM_THROW(62, "Header error : %s", LZ4F_getErrorName(nextToLoad));
    }

    /* Main Loop */
    for (;nextToLoad;) {
        size_t readSize;
        size_t pos = 0;
        size_t decodedBytes = ress.dstBufferSize;

        /* Read input */
        if (nextToLoad > ress.srcBufferSize) nextToLoad = ress.srcBufferSize;
        readSize = fread(ress.srcBuffer, 1, nextToLoad, srcFile);
        if (!readSize) break;   /* reached end of file or stream */

        while ((pos < readSize) || (decodedBytes == ress.dstBufferSize)) {  /* still to read, or still to flush */
            /* Decode Input (at least partially) */
            size_t remaining = readSize - pos;
            decodedBytes = ress.dstBufferSize;
            nextToLoad = LZ4F_decompress_usingDict(ress.dCtx, ress.dstBuffer, &decodedBytes, (char*)(ress.srcBuffer)+pos, &remaining, ress.dictBuffer, ress.dictBufferSize, NULL);
            if (LZ4F_isError(nextToLoad)) EXM_THROW(66, "Decompression error : %s", LZ4F_getErrorName(nextToLoad));
            pos += remaining;

            /* Write Block */
            if (decodedBytes) {
                if (!prefs->testMode)
                    storedSkips = LZ4IO_fwriteSparse(prefs, dstFile, ress.dstBuffer, decodedBytes, storedSkips);
                filesize += decodedBytes;
                DISPLAYUPDATE(2, "\rDecompressed : %u MB  ", (unsigned)(filesize>>20));
            }

            if (!nextToLoad) break;
        }
    }
    /* can be out because readSize == 0, which could be an fread() error */
    if (ferror(srcFile)) EXM_THROW(67, "Read error");

    if (!prefs->testMode) LZ4IO_fwriteSparseEnd(dstFile, storedSkips);
    if (nextToLoad!=0) EXM_THROW(68, "Unfinished stream");

    return filesize;
}