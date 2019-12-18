#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ZSTD_cParameter ;
struct TYPE_8__ {unsigned int enableLdm; unsigned int hashLog; unsigned int minMatchLength; unsigned int bucketSizeLog; unsigned int hashEveryLog; } ;
struct TYPE_7__ {unsigned int contentSizeFlag; unsigned int checksumFlag; int /*<<< orphan*/  noDictIDFlag; } ;
struct TYPE_6__ {unsigned int windowLog; unsigned int hashLog; unsigned int chainLog; unsigned int searchLog; unsigned int searchLength; unsigned int targetLength; int /*<<< orphan*/  strategy; } ;
struct TYPE_9__ {unsigned int format; unsigned int compressionLevel; unsigned int forceWindow; unsigned int attachDictPref; unsigned int nbWorkers; unsigned int jobSize; unsigned int overlapSizeLog; TYPE_3__ ldmParams; TYPE_2__ fParams; TYPE_1__ cParams; } ;
typedef  TYPE_4__ ZSTD_CCtx_params ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTD_CCtxParam_getParameter(
        ZSTD_CCtx_params* CCtxParams, ZSTD_cParameter param, unsigned* value)
{
    switch(param)
    {
    case ZSTD_p_format :
        *value = CCtxParams->format;
        break;
    case ZSTD_p_compressionLevel :
        *value = CCtxParams->compressionLevel;
        break;
    case ZSTD_p_windowLog :
        *value = CCtxParams->cParams.windowLog;
        break;
    case ZSTD_p_hashLog :
        *value = CCtxParams->cParams.hashLog;
        break;
    case ZSTD_p_chainLog :
        *value = CCtxParams->cParams.chainLog;
        break;
    case ZSTD_p_searchLog :
        *value = CCtxParams->cParams.searchLog;
        break;
    case ZSTD_p_minMatch :
        *value = CCtxParams->cParams.searchLength;
        break;
    case ZSTD_p_targetLength :
        *value = CCtxParams->cParams.targetLength;
        break;
    case ZSTD_p_compressionStrategy :
        *value = (unsigned)CCtxParams->cParams.strategy;
        break;
    case ZSTD_p_contentSizeFlag :
        *value = CCtxParams->fParams.contentSizeFlag;
        break;
    case ZSTD_p_checksumFlag :
        *value = CCtxParams->fParams.checksumFlag;
        break;
    case ZSTD_p_dictIDFlag :
        *value = !CCtxParams->fParams.noDictIDFlag;
        break;
    case ZSTD_p_forceMaxWindow :
        *value = CCtxParams->forceWindow;
        break;
    case ZSTD_p_forceAttachDict :
        *value = CCtxParams->attachDictPref;
        break;
    case ZSTD_p_nbWorkers :
#ifndef ZSTD_MULTITHREAD
        assert(CCtxParams->nbWorkers == 0);
#endif
        *value = CCtxParams->nbWorkers;
        break;
    case ZSTD_p_jobSize :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        *value = CCtxParams->jobSize;
        break;
#endif
    case ZSTD_p_overlapSizeLog :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        *value = CCtxParams->overlapSizeLog;
        break;
#endif
    case ZSTD_p_enableLongDistanceMatching :
        *value = CCtxParams->ldmParams.enableLdm;
        break;
    case ZSTD_p_ldmHashLog :
        *value = CCtxParams->ldmParams.hashLog;
        break;
    case ZSTD_p_ldmMinMatch :
        *value = CCtxParams->ldmParams.minMatchLength;
        break;
    case ZSTD_p_ldmBucketSizeLog :
        *value = CCtxParams->ldmParams.bucketSizeLog;
        break;
    case ZSTD_p_ldmHashEveryLog :
        *value = CCtxParams->ldmParams.hashEveryLog;
        break;
    default: return ERROR(parameter_unsupported);
    }
    return 0;
}