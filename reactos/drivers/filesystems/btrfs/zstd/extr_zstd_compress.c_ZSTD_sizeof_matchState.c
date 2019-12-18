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
typedef  int /*<<< orphan*/  ZSTD_optimal_t ;
typedef  int /*<<< orphan*/  ZSTD_match_t ;
struct TYPE_3__ {scalar_t__ strategy; size_t chainLog; size_t hashLog; int searchLength; int /*<<< orphan*/  windowLog; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
typedef  size_t U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,size_t,size_t,size_t) ; 
 int Litbits ; 
 size_t MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MaxLL ; 
 int MaxML ; 
 int MaxOff ; 
 int /*<<< orphan*/  ZSTD_HASHLOG3_MAX ; 
 int ZSTD_OPT_NUM ; 
 scalar_t__ ZSTD_btopt ; 
 scalar_t__ ZSTD_btultra ; 
 scalar_t__ ZSTD_fast ; 

__attribute__((used)) static size_t
ZSTD_sizeof_matchState(const ZSTD_compressionParameters* const cParams,
                       const U32 forCCtx)
{
    size_t const chainSize = (cParams->strategy == ZSTD_fast) ? 0 : ((size_t)1 << cParams->chainLog);
    size_t const hSize = ((size_t)1) << cParams->hashLog;
    U32    const hashLog3 = (forCCtx && cParams->searchLength==3) ? MIN(ZSTD_HASHLOG3_MAX, cParams->windowLog) : 0;
    size_t const h3Size = ((size_t)1) << hashLog3;
    size_t const tableSpace = (chainSize + hSize + h3Size) * sizeof(U32);
    size_t const optPotentialSpace = ((MaxML+1) + (MaxLL+1) + (MaxOff+1) + (1<<Litbits)) * sizeof(U32)
                          + (ZSTD_OPT_NUM+1) * (sizeof(ZSTD_match_t)+sizeof(ZSTD_optimal_t));
    size_t const optSpace = (forCCtx && ((cParams->strategy == ZSTD_btopt) ||
                                         (cParams->strategy == ZSTD_btultra)))
                                ? optPotentialSpace
                                : 0;
    DEBUGLOG(4, "chainSize: %u - hSize: %u - h3Size: %u",
                (U32)chainSize, (U32)hSize, (U32)h3Size);
    return tableSpace + optSpace;
}