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
struct TYPE_3__ {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_compress_usingCDict_advanced (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int /*<<< orphan*/  const*,TYPE_1__ const) ; 

size_t ZSTD_compress_usingCDict(ZSTD_CCtx* cctx,
                                void* dst, size_t dstCapacity,
                                const void* src, size_t srcSize,
                                const ZSTD_CDict* cdict)
{
    ZSTD_frameParameters const fParams = { 1 /*content*/, 0 /*checksum*/, 0 /*noDictID*/ };
    return ZSTD_compress_usingCDict_advanced(cctx, dst, dstCapacity, src, srcSize, cdict, fParams);
}