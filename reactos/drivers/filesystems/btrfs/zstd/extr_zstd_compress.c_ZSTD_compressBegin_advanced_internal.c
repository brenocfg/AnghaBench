#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictTableLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_6__ {int /*<<< orphan*/  windowLog; } ;
struct TYPE_5__ {TYPE_4__ cParams; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_checkCParams (TYPE_4__) ; 
 size_t ZSTD_compressBegin_internal (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDb_not_buffered ; 

size_t ZSTD_compressBegin_advanced_internal(ZSTD_CCtx* cctx,
                                    const void* dict, size_t dictSize,
                                    ZSTD_dictContentType_e dictContentType,
                                    ZSTD_dictTableLoadMethod_e dtlm,
                                    const ZSTD_CDict* cdict,
                                    ZSTD_CCtx_params params,
                                    unsigned long long pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_compressBegin_advanced_internal: wlog=%u", params.cParams.windowLog);
    /* compression parameters verification and optimization */
    CHECK_F( ZSTD_checkCParams(params.cParams) );
    return ZSTD_compressBegin_internal(cctx,
                                       dict, dictSize, dictContentType, dtlm,
                                       cdict,
                                       params, pledgedSrcSize,
                                       ZSTDb_not_buffered);
}