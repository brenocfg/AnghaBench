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
typedef  int /*<<< orphan*/  cmpBuf ;
typedef  int /*<<< orphan*/  LZ4_stream_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BLOCK_BYTES ; 
 int LZ4_COMPRESSBOUND (int) ; 
 int LZ4_compress_fast_continue (int /*<<< orphan*/ *,char* const,char*,int const,int,int) ; 
 int /*<<< orphan*/  LZ4_initStream (int /*<<< orphan*/ *,int) ; 
 scalar_t__ read_bin (int /*<<< orphan*/ *,char* const,int) ; 
 int /*<<< orphan*/  write_bin (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  write_int (int /*<<< orphan*/ *,int const) ; 

void test_compress(FILE* outFp, FILE* inpFp)
{
    LZ4_stream_t lz4Stream_body;
    LZ4_stream_t* lz4Stream = &lz4Stream_body;

    char inpBuf[2][BLOCK_BYTES];
    int  inpBufIndex = 0;

    LZ4_initStream(lz4Stream, sizeof (*lz4Stream));

    for(;;) {
        char* const inpPtr = inpBuf[inpBufIndex];
        const int inpBytes = (int) read_bin(inpFp, inpPtr, BLOCK_BYTES);
        if(0 == inpBytes) {
            break;
        }

        {
            char cmpBuf[LZ4_COMPRESSBOUND(BLOCK_BYTES)];
            const int cmpBytes = LZ4_compress_fast_continue(
                lz4Stream, inpPtr, cmpBuf, inpBytes, sizeof(cmpBuf), 1);
            if(cmpBytes <= 0) {
                break;
            }
            write_int(outFp, cmpBytes);
            write_bin(outFp, cmpBuf, (size_t) cmpBytes);
        }

        inpBufIndex = (inpBufIndex + 1) % 2;
    }

    write_int(outFp, 0);
}