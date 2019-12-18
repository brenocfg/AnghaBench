#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
struct TYPE_4__ {size_t dictSize; int /*<<< orphan*/  dictContentType; void const* dict; } ;
struct TYPE_5__ {scalar_t__ streamStage; TYPE_1__ prefixDict; int /*<<< orphan*/ * cdict; } ;
typedef  TYPE_2__ ZSTD_CCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zcss_init ; 

size_t ZSTD_CCtx_refPrefix_advanced(
        ZSTD_CCtx* cctx, const void* prefix, size_t prefixSize, ZSTD_dictContentType_e dictContentType)
{
    if (cctx->streamStage != zcss_init) return ERROR(stage_wrong);
    cctx->cdict = NULL;   /* prefix discards any prior cdict */
    cctx->prefixDict.dict = prefix;
    cctx->prefixDict.dictSize = prefixSize;
    cctx->prefixDict.dictContentType = dictContentType;
    return 0;
}