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
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 size_t LEGACY_BLOCKSIZE ; 
 unsigned int LZ4IO_fwriteSparse (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,char* const,size_t,unsigned int) ; 
 int /*<<< orphan*/  LZ4IO_fwriteSparseEnd (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int LZ4IO_readLE32 (char* const) ; 
 unsigned int LZ4_COMPRESSBOUND (size_t) ; 
 scalar_t__ LZ4_compressBound (size_t) ; 
 int LZ4_decompress_safe (char* const,char* const,int,size_t) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char* const,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char* const) ; 
 unsigned int g_magicRead ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static unsigned long long LZ4IO_decodeLegacyStream(LZ4IO_prefs_t* const prefs, FILE* finput, FILE* foutput)
{
    unsigned long long streamSize = 0;
    unsigned storedSkips = 0;

    /* Allocate Memory */
    char* const in_buff  = (char*)malloc((size_t)LZ4_compressBound(LEGACY_BLOCKSIZE));
    char* const out_buff = (char*)malloc(LEGACY_BLOCKSIZE);
    if (!in_buff || !out_buff) EXM_THROW(51, "Allocation error : not enough memory");

    /* Main Loop */
    while (1) {
        unsigned int blockSize;

        /* Block Size */
        {   size_t const sizeCheck = fread(in_buff, 1, 4, finput);
            if (sizeCheck == 0) break;                   /* Nothing to read : file read is completed */
            if (sizeCheck != 4) EXM_THROW(52, "Read error : cannot access block size "); }
            blockSize = LZ4IO_readLE32(in_buff);       /* Convert to Little Endian */
            if (blockSize > LZ4_COMPRESSBOUND(LEGACY_BLOCKSIZE)) {
            /* Cannot read next block : maybe new stream ? */
            g_magicRead = blockSize;
            break;
        }

        /* Read Block */
        { size_t const sizeCheck = fread(in_buff, 1, blockSize, finput);
          if (sizeCheck!=blockSize) EXM_THROW(52, "Read error : cannot access compressed block !"); }

        /* Decode Block */
        {   int const decodeSize = LZ4_decompress_safe(in_buff, out_buff, (int)blockSize, LEGACY_BLOCKSIZE);
            if (decodeSize < 0) EXM_THROW(53, "Decoding Failed ! Corrupted input detected !");
            streamSize += (unsigned long long)decodeSize;
            /* Write Block */
            storedSkips = LZ4IO_fwriteSparse(prefs, foutput, out_buff, (size_t)decodeSize, storedSkips); /* success or die */
    }   }
    if (ferror(finput)) EXM_THROW(54, "Read error : ferror");

    LZ4IO_fwriteSparseEnd(foutput, storedSkips);

    /* Free */
    free(in_buff);
    free(out_buff);

    return streamSize;
}