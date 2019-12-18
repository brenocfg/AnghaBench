#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_strategy ;
typedef  int /*<<< orphan*/  ZSTD_format_e ;
typedef  int ZSTD_cParameter ;
struct TYPE_10__ {int enableLdm; unsigned int hashLog; unsigned int minMatchLength; unsigned int bucketSizeLog; unsigned int hashEveryLog; } ;
struct TYPE_9__ {int contentSizeFlag; int checksumFlag; int noDictIDFlag; } ;
struct TYPE_8__ {unsigned int windowLog; unsigned int hashLog; unsigned int chainLog; unsigned int searchLog; unsigned int searchLength; unsigned int targetLength; int /*<<< orphan*/  strategy; } ;
struct TYPE_11__ {int compressionLevel; int forceWindow; size_t attachDictPref; TYPE_3__ ldmParams; TYPE_2__ fParams; TYPE_1__ cParams; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMPCHECK (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_CCtxParam_setMTCtxParameter (TYPE_4__*,int /*<<< orphan*/ ,unsigned int) ; 
 size_t ZSTDMT_CCtxParam_setNbWorkers (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  ZSTDMT_p_jobSize ; 
 int /*<<< orphan*/  ZSTDMT_p_overlapSectionLog ; 
 unsigned int ZSTD_CHAINLOG_MAX ; 
 unsigned int ZSTD_CHAINLOG_MIN ; 
 unsigned int ZSTD_HASHLOG_MAX ; 
 unsigned int ZSTD_HASHLOG_MIN ; 
 unsigned int ZSTD_LDM_BUCKETSIZELOG_MAX ; 
 unsigned int ZSTD_LDM_MINMATCH_MAX ; 
 unsigned int ZSTD_LDM_MINMATCH_MIN ; 
 unsigned int ZSTD_SEARCHLENGTH_MAX ; 
 unsigned int ZSTD_SEARCHLENGTH_MIN ; 
 unsigned int ZSTD_SEARCHLOG_MAX ; 
 unsigned int ZSTD_SEARCHLOG_MIN ; 
 unsigned int ZSTD_WINDOWLOG_MAX ; 
 unsigned int ZSTD_WINDOWLOG_MIN ; 
 int /*<<< orphan*/  ZSTD_btultra ; 
 size_t ZSTD_dictDefaultAttach ; 
 size_t ZSTD_dictForceAttach ; 
 size_t ZSTD_dictForceCopy ; 
 int /*<<< orphan*/  ZSTD_f_zstd1_magicless ; 
 int /*<<< orphan*/  ZSTD_fast ; 
 int ZSTD_maxCLevel () ; 
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
 int /*<<< orphan*/  parameter_outOfBound ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTD_CCtxParam_setParameter(
        ZSTD_CCtx_params* CCtxParams, ZSTD_cParameter param, unsigned value)
{
    DEBUGLOG(4, "ZSTD_CCtxParam_setParameter (%u, %u)", (U32)param, value);
    switch(param)
    {
    case ZSTD_p_format :
        if (value > (unsigned)ZSTD_f_zstd1_magicless)
            return ERROR(parameter_unsupported);
        CCtxParams->format = (ZSTD_format_e)value;
        return (size_t)CCtxParams->format;

    case ZSTD_p_compressionLevel : {
        int cLevel = (int)value;  /* cast expected to restore negative sign */
        if (cLevel > ZSTD_maxCLevel()) cLevel = ZSTD_maxCLevel();
        if (cLevel) {  /* 0 : does not change current level */
            CCtxParams->compressionLevel = cLevel;
        }
        if (CCtxParams->compressionLevel >= 0) return CCtxParams->compressionLevel;
        return 0;  /* return type (size_t) cannot represent negative values */
    }

    case ZSTD_p_windowLog :
        if (value>0)   /* 0 => use default */
            CLAMPCHECK(value, ZSTD_WINDOWLOG_MIN, ZSTD_WINDOWLOG_MAX);
        CCtxParams->cParams.windowLog = value;
        return CCtxParams->cParams.windowLog;

    case ZSTD_p_hashLog :
        if (value>0)   /* 0 => use default */
            CLAMPCHECK(value, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
        CCtxParams->cParams.hashLog = value;
        return CCtxParams->cParams.hashLog;

    case ZSTD_p_chainLog :
        if (value>0)   /* 0 => use default */
            CLAMPCHECK(value, ZSTD_CHAINLOG_MIN, ZSTD_CHAINLOG_MAX);
        CCtxParams->cParams.chainLog = value;
        return CCtxParams->cParams.chainLog;

    case ZSTD_p_searchLog :
        if (value>0)   /* 0 => use default */
            CLAMPCHECK(value, ZSTD_SEARCHLOG_MIN, ZSTD_SEARCHLOG_MAX);
        CCtxParams->cParams.searchLog = value;
        return value;

    case ZSTD_p_minMatch :
        if (value>0)   /* 0 => use default */
            CLAMPCHECK(value, ZSTD_SEARCHLENGTH_MIN, ZSTD_SEARCHLENGTH_MAX);
        CCtxParams->cParams.searchLength = value;
        return CCtxParams->cParams.searchLength;

    case ZSTD_p_targetLength :
        /* all values are valid. 0 => use default */
        CCtxParams->cParams.targetLength = value;
        return CCtxParams->cParams.targetLength;

    case ZSTD_p_compressionStrategy :
        if (value>0)   /* 0 => use default */
            CLAMPCHECK(value, (unsigned)ZSTD_fast, (unsigned)ZSTD_btultra);
        CCtxParams->cParams.strategy = (ZSTD_strategy)value;
        return (size_t)CCtxParams->cParams.strategy;

    case ZSTD_p_contentSizeFlag :
        /* Content size written in frame header _when known_ (default:1) */
        DEBUGLOG(4, "set content size flag = %u", (value>0));
        CCtxParams->fParams.contentSizeFlag = value > 0;
        return CCtxParams->fParams.contentSizeFlag;

    case ZSTD_p_checksumFlag :
        /* A 32-bits content checksum will be calculated and written at end of frame (default:0) */
        CCtxParams->fParams.checksumFlag = value > 0;
        return CCtxParams->fParams.checksumFlag;

    case ZSTD_p_dictIDFlag : /* When applicable, dictionary's dictID is provided in frame header (default:1) */
        DEBUGLOG(4, "set dictIDFlag = %u", (value>0));
        CCtxParams->fParams.noDictIDFlag = !value;
        return !CCtxParams->fParams.noDictIDFlag;

    case ZSTD_p_forceMaxWindow :
        CCtxParams->forceWindow = (value > 0);
        return CCtxParams->forceWindow;

    case ZSTD_p_forceAttachDict :
        CCtxParams->attachDictPref = value ?
                                    (value > 0 ? ZSTD_dictForceAttach : ZSTD_dictForceCopy) :
                                     ZSTD_dictDefaultAttach;
        return CCtxParams->attachDictPref;

    case ZSTD_p_nbWorkers :
#ifndef ZSTD_MULTITHREAD
        if (value>0) return ERROR(parameter_unsupported);
        return 0;
#else
        return ZSTDMT_CCtxParam_setNbWorkers(CCtxParams, value);
#endif

    case ZSTD_p_jobSize :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        return ZSTDMT_CCtxParam_setMTCtxParameter(CCtxParams, ZSTDMT_p_jobSize, value);
#endif

    case ZSTD_p_overlapSizeLog :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        return ZSTDMT_CCtxParam_setMTCtxParameter(CCtxParams, ZSTDMT_p_overlapSectionLog, value);
#endif

    case ZSTD_p_enableLongDistanceMatching :
        CCtxParams->ldmParams.enableLdm = (value>0);
        return CCtxParams->ldmParams.enableLdm;

    case ZSTD_p_ldmHashLog :
        if (value>0)   /* 0 ==> auto */
            CLAMPCHECK(value, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
        CCtxParams->ldmParams.hashLog = value;
        return CCtxParams->ldmParams.hashLog;

    case ZSTD_p_ldmMinMatch :
        if (value>0)   /* 0 ==> default */
            CLAMPCHECK(value, ZSTD_LDM_MINMATCH_MIN, ZSTD_LDM_MINMATCH_MAX);
        CCtxParams->ldmParams.minMatchLength = value;
        return CCtxParams->ldmParams.minMatchLength;

    case ZSTD_p_ldmBucketSizeLog :
        if (value > ZSTD_LDM_BUCKETSIZELOG_MAX)
            return ERROR(parameter_outOfBound);
        CCtxParams->ldmParams.bucketSizeLog = value;
        return CCtxParams->ldmParams.bucketSizeLog;

    case ZSTD_p_ldmHashEveryLog :
        if (value > ZSTD_WINDOWLOG_MAX - ZSTD_HASHLOG_MIN)
            return ERROR(parameter_outOfBound);
        CCtxParams->ldmParams.hashEveryLog = value;
        return CCtxParams->ldmParams.hashEveryLog;

    default: return ERROR(parameter_unsupported);
    }
}