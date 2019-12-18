#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 size_t ZSTD_compress_internal (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,void const*,size_t,TYPE_1__) ; 

size_t ZSTD_compress_advanced (ZSTD_CCtx* cctx,
                               void* dst, size_t dstCapacity,
                         const void* src, size_t srcSize,
                         const void* dict,size_t dictSize,
                               ZSTD_parameters params)
{
    DEBUGLOG(4, "ZSTD_compress_advanced");
    CHECK_F(ZSTD_checkCParams(params.cParams));
    return ZSTD_compress_internal(cctx,
                                  dst, dstCapacity,
                                  src, srcSize,
                                  dict, dictSize,
                                  params);
}