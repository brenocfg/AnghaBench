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
typedef  int ZSTD_cParameter ;

/* Variables and functions */
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

__attribute__((used)) static int ZSTD_isUpdateAuthorized(ZSTD_cParameter param)
{
    switch(param)
    {
    case ZSTD_p_compressionLevel:
    case ZSTD_p_hashLog:
    case ZSTD_p_chainLog:
    case ZSTD_p_searchLog:
    case ZSTD_p_minMatch:
    case ZSTD_p_targetLength:
    case ZSTD_p_compressionStrategy:
        return 1;

    case ZSTD_p_format:
    case ZSTD_p_windowLog:
    case ZSTD_p_contentSizeFlag:
    case ZSTD_p_checksumFlag:
    case ZSTD_p_dictIDFlag:
    case ZSTD_p_forceMaxWindow :
    case ZSTD_p_nbWorkers:
    case ZSTD_p_jobSize:
    case ZSTD_p_overlapSizeLog:
    case ZSTD_p_enableLongDistanceMatching:
    case ZSTD_p_ldmHashLog:
    case ZSTD_p_ldmMinMatch:
    case ZSTD_p_ldmBucketSizeLog:
    case ZSTD_p_ldmHashEveryLog:
    case ZSTD_p_forceAttachDict:
    default:
        return 0;
    }
}