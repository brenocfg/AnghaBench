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
typedef  scalar_t__ o_scenario_e ;
typedef  int /*<<< orphan*/  U64 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  LZ4F_dctx ;

/* Variables and functions */
 int FUZ_rand (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (size_t const) ; 
 scalar_t__ const o_noncontiguous ; 
 size_t test_lz4f_decompression_wBuffers (void const*,size_t,void* const,size_t const,scalar_t__ const,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t test_lz4f_decompression(const void* cSrc, size_t cSize,
                               const void* srcRef, size_t decompressedSize,
                               U64 crcOrig,
                               U32* const randState,
                               LZ4F_dctx* const dCtx,
                               U32 seed, U32 testNb)
{
    o_scenario_e const o_scenario = (o_scenario_e)(FUZ_rand(randState) % 3);   /* 0 : contiguous; 1 : non-contiguous; 2 : dst overwritten */
    /* tighten dst buffer conditions */
    size_t const dstCapacity = (o_scenario == o_noncontiguous) ?
                               (decompressedSize * 2) + 128 :
                               decompressedSize;
    size_t result;
    void* const dstBuffer = malloc(dstCapacity);
    assert(dstBuffer != NULL);

    result = test_lz4f_decompression_wBuffers(cSrc, cSize,
                                     dstBuffer, dstCapacity, o_scenario,
                                     srcRef, decompressedSize,
                                     crcOrig,
                                     randState,
                                     dCtx,
                                     seed, testNb);

    free(dstBuffer);
    return result;
}