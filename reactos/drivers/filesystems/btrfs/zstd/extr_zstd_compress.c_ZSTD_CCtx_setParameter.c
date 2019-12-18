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
typedef  int ZSTD_cParameter ;
struct TYPE_3__ {scalar_t__ streamStage; int cParamsChanged; int /*<<< orphan*/  requestedParams; int /*<<< orphan*/  cdict; int /*<<< orphan*/  staticSize; } ;
typedef  TYPE_1__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ,unsigned int) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_CCtxParam_setParameter (int /*<<< orphan*/ *,int,unsigned int) ; 
 scalar_t__ ZSTD_isUpdateAuthorized (int) ; 
#define  ZSTD_p_chainLog 149 
#define  ZSTD_p_checksumFlag 148 
#define  ZSTD_p_compressionLevel 147 
#define  ZSTD_p_compressionStrategy 146 
#define  ZSTD_p_contentSizeFlag 145 
#define  ZSTD_p_dictIDFlag 144 
#define  ZSTD_p_enableLongDistanceMatching 143 
#define  ZSTD_p_forceAttachDict 142 
#define  ZSTD_p_forceMaxWindow 141 
#define  ZSTD_p_format 140 
#define  ZSTD_p_hashLog 139 
#define  ZSTD_p_jobSize 138 
#define  ZSTD_p_ldmBucketSizeLog 137 
#define  ZSTD_p_ldmHashEveryLog 136 
#define  ZSTD_p_ldmHashLog 135 
#define  ZSTD_p_ldmMinMatch 134 
#define  ZSTD_p_minMatch 133 
#define  ZSTD_p_nbWorkers 132 
#define  ZSTD_p_overlapSizeLog 131 
#define  ZSTD_p_searchLog 130 
#define  ZSTD_p_targetLength 129 
#define  ZSTD_p_windowLog 128 
 int /*<<< orphan*/  parameter_unsupported ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zcss_init ; 

size_t ZSTD_CCtx_setParameter(ZSTD_CCtx* cctx, ZSTD_cParameter param, unsigned value)
{
    DEBUGLOG(4, "ZSTD_CCtx_setParameter (%u, %u)", (U32)param, value);
    if (cctx->streamStage != zcss_init) {
        if (ZSTD_isUpdateAuthorized(param)) {
            cctx->cParamsChanged = 1;
        } else {
            return ERROR(stage_wrong);
    }   }

    switch(param)
    {
    case ZSTD_p_format :
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_compressionLevel:
        if (cctx->cdict) return ERROR(stage_wrong);
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_windowLog:
    case ZSTD_p_hashLog:
    case ZSTD_p_chainLog:
    case ZSTD_p_searchLog:
    case ZSTD_p_minMatch:
    case ZSTD_p_targetLength:
    case ZSTD_p_compressionStrategy:
        if (cctx->cdict) return ERROR(stage_wrong);
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_contentSizeFlag:
    case ZSTD_p_checksumFlag:
    case ZSTD_p_dictIDFlag:
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_forceMaxWindow :  /* Force back-references to remain < windowSize,
                                   * even when referencing into Dictionary content.
                                   * default : 0 when using a CDict, 1 when using a Prefix */
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_forceAttachDict:
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_nbWorkers:
        if ((value>0) && cctx->staticSize) {
            return ERROR(parameter_unsupported);  /* MT not compatible with static alloc */
        }
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_jobSize:
    case ZSTD_p_overlapSizeLog:
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    case ZSTD_p_enableLongDistanceMatching:
    case ZSTD_p_ldmHashLog:
    case ZSTD_p_ldmMinMatch:
    case ZSTD_p_ldmBucketSizeLog:
    case ZSTD_p_ldmHashEveryLog:
        if (cctx->cdict) return ERROR(stage_wrong);
        return ZSTD_CCtxParam_setParameter(&cctx->requestedParams, param, value);

    default: return ERROR(parameter_unsupported);
    }
}