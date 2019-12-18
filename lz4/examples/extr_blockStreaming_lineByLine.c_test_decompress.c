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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  LZ4_streamDecode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LZ4_COMPRESSBOUND (size_t) ; 
 int /*<<< orphan*/ * LZ4_createStreamDecode () ; 
 int LZ4_decompress_safe_continue (int /*<<< orphan*/ * const,char* const,char* const,scalar_t__,int) ; 
 int /*<<< orphan*/  LZ4_freeStreamDecode (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  free (char* const) ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ read_bin (int /*<<< orphan*/ *,char* const,scalar_t__) ; 
 int read_uint16 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  write_bin (int /*<<< orphan*/ *,char* const,int const) ; 

__attribute__((used)) static void test_decompress(
    FILE* outFp,
    FILE* inpFp,
    size_t messageMaxBytes,
    size_t ringBufferBytes)
{
    LZ4_streamDecode_t* const lz4StreamDecode = LZ4_createStreamDecode();
    char* const cmpBuf = (char*) malloc(LZ4_COMPRESSBOUND(messageMaxBytes));
    char* const decBuf = (char*) malloc(ringBufferBytes);
    int decOffset = 0;

    for ( ; ; )
    {
        uint16_t cmpBytes = 0;

        if (read_uint16(inpFp, &cmpBytes) != 1) break;
        if (cmpBytes == 0) break;
        if (read_bin(inpFp, cmpBuf, cmpBytes) != cmpBytes) break;

        {
            char* const decPtr = &decBuf[decOffset];
            const int decBytes = LZ4_decompress_safe_continue(
                lz4StreamDecode, cmpBuf, decPtr, cmpBytes, (int) messageMaxBytes);
            if (decBytes <= 0) break;
            write_bin(outFp, decPtr, decBytes);

            // Add and wraparound the ringbuffer offset
            decOffset += decBytes;
            if ((size_t)decOffset >= ringBufferBytes - messageMaxBytes) decOffset = 0;
        }
    }

    free(decBuf);
    free(cmpBuf);
    LZ4_freeStreamDecode(lz4StreamDecode);
}