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
typedef  scalar_t__ state ;
struct TYPE_3__ {int /*<<< orphan*/  internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamHC_t ;
typedef  int /*<<< orphan*/  LZ4HC_CCtx_internal ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int LZ4HC_compress_generic (int /*<<< orphan*/ * const,char const*,char*,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4HC_init_internal (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*) ; 
 int LZ4_compressBound (int) ; 
 int /*<<< orphan*/  LZ4_resetStreamHC_fast (TYPE_1__*,int) ; 
 int LZ4_streamHC_t_alignment () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  limitedOutput ; 
 int /*<<< orphan*/  notLimited ; 

int LZ4_compress_HC_extStateHC_fastReset (void* state, const char* src, char* dst, int srcSize, int dstCapacity, int compressionLevel)
{
    LZ4HC_CCtx_internal* const ctx = &((LZ4_streamHC_t*)state)->internal_donotuse;
#ifndef _MSC_VER  /* for some reason, Visual fails the aligment test on 32-bit x86 :
                   * it reports an aligment of 8-bytes,
                   * while actually aligning LZ4_streamHC_t on 4 bytes. */
    assert(((size_t)state & (LZ4_streamHC_t_alignment() - 1)) == 0);  /* check alignment */
#endif
    if (((size_t)(state)&(sizeof(void*)-1)) != 0) return 0;   /* Error : state is not aligned for pointers (32 or 64 bits) */
    LZ4_resetStreamHC_fast((LZ4_streamHC_t*)state, compressionLevel);
    LZ4HC_init_internal (ctx, (const BYTE*)src);
    if (dstCapacity < LZ4_compressBound(srcSize))
        return LZ4HC_compress_generic (ctx, src, dst, &srcSize, dstCapacity, compressionLevel, limitedOutput);
    else
        return LZ4HC_compress_generic (ctx, src, dst, &srcSize, dstCapacity, compressionLevel, notLimited);
}