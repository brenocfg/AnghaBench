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
typedef  int /*<<< orphan*/  ZSTD_longOffset_e ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 size_t ZSTD_decompressSequences_body (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static size_t
ZSTD_decompressSequences_default(ZSTD_DCtx* dctx,
                                 void* dst, size_t maxDstSize,
                           const void* seqStart, size_t seqSize, int nbSeq,
                           const ZSTD_longOffset_e isLongOffset)
{
    return ZSTD_decompressSequences_body(dctx, dst, maxDstSize, seqStart, seqSize, nbSeq, isLongOffset);
}