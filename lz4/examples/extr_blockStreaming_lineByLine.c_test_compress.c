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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  LZ4_stream_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LZ4_COMPRESSBOUND (size_t) ; 
 int LZ4_compress_fast_continue (int /*<<< orphan*/ * const,char* const,char* const,int,size_t const,int) ; 
 int /*<<< orphan*/ * LZ4_createStream () ; 
 int /*<<< orphan*/  LZ4_freeStream (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  fgets (char* const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char* const) ; 
 scalar_t__ malloc (size_t const) ; 
 size_t rand () ; 
 scalar_t__ read_bin (int /*<<< orphan*/ *,char* const,int const) ; 
 scalar_t__ strlen (char* const) ; 
 int /*<<< orphan*/  write_bin (int /*<<< orphan*/ *,char* const,int const) ; 
 int /*<<< orphan*/  write_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_compress(
    FILE* outFp,
    FILE* inpFp,
    size_t messageMaxBytes,
    size_t ringBufferBytes)
{
    LZ4_stream_t* const lz4Stream = LZ4_createStream();
    const size_t cmpBufBytes = LZ4_COMPRESSBOUND(messageMaxBytes);
    char* const cmpBuf = (char*) malloc(cmpBufBytes);
    char* const inpBuf = (char*) malloc(ringBufferBytes);
    int inpOffset = 0;

    for ( ; ; )
    {
        char* const inpPtr = &inpBuf[inpOffset];

#if 0
        // Read random length data to the ring buffer.
        const int randomLength = (rand() % messageMaxBytes) + 1;
        const int inpBytes = (int) read_bin(inpFp, inpPtr, randomLength);
        if (0 == inpBytes) break;
#else
        // Read line to the ring buffer.
        int inpBytes = 0;
        if (!fgets(inpPtr, (int) messageMaxBytes, inpFp))
            break;
        inpBytes = (int) strlen(inpPtr);
#endif

        {
            const int cmpBytes = LZ4_compress_fast_continue(
                lz4Stream, inpPtr, cmpBuf, inpBytes, cmpBufBytes, 1);
            if (cmpBytes <= 0) break;
            write_uint16(outFp, (uint16_t) cmpBytes);
            write_bin(outFp, cmpBuf, cmpBytes);

            // Add and wraparound the ringbuffer offset
            inpOffset += inpBytes;
            if ((size_t)inpOffset >= ringBufferBytes - messageMaxBytes) inpOffset = 0;
        }
    }
    write_uint16(outFp, 0);

    free(inpBuf);
    free(cmpBuf);
    LZ4_freeStream(lz4Stream);
}