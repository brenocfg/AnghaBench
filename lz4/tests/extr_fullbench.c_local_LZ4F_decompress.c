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
 int /*<<< orphan*/  DISPLAY (char*) ; 
 size_t LZ4F_decompress (int /*<<< orphan*/ ,char*,size_t*,char const*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  g_dCtx ; 

__attribute__((used)) static int local_LZ4F_decompress(const char* in, char* out, int inSize, int outSize)
{
    size_t srcSize = (size_t)inSize;
    size_t dstSize = (size_t)outSize;
    size_t result;
    assert(inSize >= 0);
    assert(outSize >= 0);
    result = LZ4F_decompress(g_dCtx, out, &dstSize, in, &srcSize, NULL);
    if (result!=0) { DISPLAY("Error decompressing frame : unfinished frame \n"); exit(8); }
    if (srcSize != (size_t)inSize) { DISPLAY("Error decompressing frame : read size incorrect \n"); exit(9); }
    return (int)dstSize;
}