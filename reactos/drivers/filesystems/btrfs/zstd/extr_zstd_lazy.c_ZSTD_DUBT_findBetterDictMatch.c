#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* base; int dictLimit; scalar_t__* nextSrc; int lowLimit; } ;
struct TYPE_7__ {int hashLog; int chainLog; } ;
struct TYPE_6__ {int* hashTable; int* chainTable; TYPE_1__ window; TYPE_3__ cParams; struct TYPE_6__* dictMatchState; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;
typedef  scalar_t__ ZSTD_dictMode_e ;
typedef  TYPE_3__ ZSTD_compressionParameters ;
typedef  int U32 ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int const,int,int,int const,...) ; 
 size_t MIN (size_t,size_t) ; 
 size_t MINMATCH ; 
 int const ZSTD_REP_MOVE ; 
 scalar_t__ ZSTD_count_2segments (scalar_t__ const* const,scalar_t__ const*,scalar_t__ const* const,scalar_t__ const* const,scalar_t__ const* const) ; 
 scalar_t__ const ZSTD_dictMatchState ; 
 size_t ZSTD_hashPtr (scalar_t__ const* const,int const,int const) ; 
 scalar_t__ ZSTD_highbit32 (int const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t
ZSTD_DUBT_findBetterDictMatch (
        ZSTD_matchState_t* ms,
        const BYTE* const ip, const BYTE* const iend,
        size_t* offsetPtr,
        size_t bestLength,
        U32 nbCompares,
        U32 const mls,
        const ZSTD_dictMode_e dictMode)
{
    const ZSTD_matchState_t * const dms = ms->dictMatchState;
    const ZSTD_compressionParameters* const dmsCParams = &dms->cParams;
    const U32 * const dictHashTable = dms->hashTable;
    U32         const hashLog = dmsCParams->hashLog;
    size_t      const h  = ZSTD_hashPtr(ip, hashLog, mls);
    U32               dictMatchIndex = dictHashTable[h];

    const BYTE* const base = ms->window.base;
    const BYTE* const prefixStart = base + ms->window.dictLimit;
    U32         const current = (U32)(ip-base);
    const BYTE* const dictBase = dms->window.base;
    const BYTE* const dictEnd = dms->window.nextSrc;
    U32         const dictHighLimit = (U32)(dms->window.nextSrc - dms->window.base);
    U32         const dictLowLimit = dms->window.lowLimit;
    U32         const dictIndexDelta = ms->window.lowLimit - dictHighLimit;

    U32*        const dictBt = dms->chainTable;
    U32         const btLog  = dmsCParams->chainLog - 1;
    U32         const btMask = (1 << btLog) - 1;
    U32         const btLow = (btMask >= dictHighLimit - dictLowLimit) ? dictLowLimit : dictHighLimit - btMask;

    size_t commonLengthSmaller=0, commonLengthLarger=0;

    (void)dictMode;
    assert(dictMode == ZSTD_dictMatchState);

    while (nbCompares-- && (dictMatchIndex > dictLowLimit)) {
        U32* const nextPtr = dictBt + 2*(dictMatchIndex & btMask);
        size_t matchLength = MIN(commonLengthSmaller, commonLengthLarger);   /* guaranteed minimum nb of common bytes */
        const BYTE* match = dictBase + dictMatchIndex;
        matchLength += ZSTD_count_2segments(ip+matchLength, match+matchLength, iend, dictEnd, prefixStart);
        if (dictMatchIndex+matchLength >= dictHighLimit)
            match = base + dictMatchIndex + dictIndexDelta;   /* to prepare for next usage of match[matchLength] */

        if (matchLength > bestLength) {
            U32 matchIndex = dictMatchIndex + dictIndexDelta;
            if ( (4*(int)(matchLength-bestLength)) > (int)(ZSTD_highbit32(current-matchIndex+1) - ZSTD_highbit32((U32)offsetPtr[0]+1)) ) {
                DEBUGLOG(9, "ZSTD_DUBT_findBetterDictMatch(%u) : found better match length %u -> %u and offsetCode %u -> %u (dictMatchIndex %u, matchIndex %u)",
                    current, (U32)bestLength, (U32)matchLength, (U32)*offsetPtr, ZSTD_REP_MOVE + current - matchIndex, dictMatchIndex, matchIndex);
                bestLength = matchLength, *offsetPtr = ZSTD_REP_MOVE + current - matchIndex;
            }
            if (ip+matchLength == iend) {   /* reached end of input : ip[matchLength] is not valid, no way to know if it's larger or smaller than match */
                break;   /* drop, to guarantee consistency (miss a little bit of compression) */
            }
        }

        if (match[matchLength] < ip[matchLength]) {
            if (dictMatchIndex <= btLow) { break; }   /* beyond tree size, stop the search */
            commonLengthSmaller = matchLength;    /* all smaller will now have at least this guaranteed common length */
            dictMatchIndex = nextPtr[1];              /* new matchIndex larger than previous (closer to current) */
        } else {
            /* match is larger than current */
            if (dictMatchIndex <= btLow) { break; }   /* beyond tree size, stop the search */
            commonLengthLarger = matchLength;
            dictMatchIndex = nextPtr[0];
        }
    }

    if (bestLength >= MINMATCH) {
        U32 const mIndex = current - ((U32)*offsetPtr - ZSTD_REP_MOVE); (void)mIndex;
        DEBUGLOG(8, "ZSTD_DUBT_findBetterDictMatch(%u) : found match of length %u and offsetCode %u (pos %u)",
                    current, (U32)bestLength, (U32)*offsetPtr, mIndex);
    }
    return bestLength;

}