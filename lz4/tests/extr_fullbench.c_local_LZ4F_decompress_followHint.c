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

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,unsigned int,unsigned int) ; 
 size_t LZ4F_decompress (int /*<<< orphan*/ ,char*,size_t*,char const*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  g_dCtx ; 

__attribute__((used)) static int local_LZ4F_decompress_followHint(const char* src, char* dst, int srcSize, int dstSize)
{
    size_t totalInSize = (size_t)srcSize;
    size_t maxOutSize = (size_t)dstSize;

    size_t inPos = 0;
    size_t inSize = 0;
    size_t outPos = 0;
    size_t outRemaining = maxOutSize - outPos;

    for (;;) {
        size_t const sizeHint = LZ4F_decompress(g_dCtx, dst+outPos, &outRemaining, src+inPos, &inSize, NULL);
        assert(!LZ4F_isError(sizeHint));

        inPos += inSize;
        inSize = sizeHint;

        outPos += outRemaining;
        outRemaining = maxOutSize - outPos;

        if (!sizeHint) break;
    }

    /* frame completed */
    if (inPos != totalInSize) {
        DISPLAY("Error decompressing frame : must read (%u) full frame (%u) \n",
                (unsigned)inPos, (unsigned)totalInSize);
        exit(10);
    }
    return (int)outPos;

}