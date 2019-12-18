#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpRep ;
struct TYPE_11__ {scalar_t__ sequences; scalar_t__ sequencesStart; } ;
typedef  TYPE_2__ seqStore_t ;
struct TYPE_13__ {scalar_t__ litLengthSum; } ;
struct TYPE_10__ {scalar_t__ dictLimit; scalar_t__ lowLimit; size_t base; } ;
struct TYPE_12__ {scalar_t__ nextToUpdate; scalar_t__ nextToUpdate3; TYPE_4__ opt; TYPE_1__ window; } ;
typedef  TYPE_3__ ZSTD_matchState_t ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 size_t ZSTD_BLOCKSIZE_MAX ; 
 int ZSTD_REP_NUM ; 
 size_t ZSTD_compressBlock_opt_generic (TYPE_3__*,TYPE_2__*,scalar_t__*,void const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_noDict ; 
 int /*<<< orphan*/  ZSTD_resetSeqStore (TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_upscaleStats (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

size_t ZSTD_compressBlock_btultra(
        ZSTD_matchState_t* ms, seqStore_t* seqStore, U32 rep[ZSTD_REP_NUM],
        const void* src, size_t srcSize)
{
    DEBUGLOG(5, "ZSTD_compressBlock_btultra (srcSize=%zu)", srcSize);
#if 0
    /* 2-pass strategy (disabled)
     * this strategy makes a first pass over first block to collect statistics
     * and seed next round's statistics with it.
     * The compression ratio gain is generally small (~0.5% on first block),
     * the cost is 2x cpu time on first block. */
    assert(srcSize <= ZSTD_BLOCKSIZE_MAX);
    if ( (ms->opt.litLengthSum==0)   /* first block */
      && (seqStore->sequences == seqStore->sequencesStart)   /* no ldm */
      && (ms->window.dictLimit == ms->window.lowLimit) ) {   /* no dictionary */
        U32 tmpRep[ZSTD_REP_NUM];
        DEBUGLOG(5, "ZSTD_compressBlock_btultra: first block: collecting statistics");
        assert(ms->nextToUpdate >= ms->window.dictLimit
            && ms->nextToUpdate <= ms->window.dictLimit + 1);
        memcpy(tmpRep, rep, sizeof(tmpRep));
        ZSTD_compressBlock_opt_generic(ms, seqStore, tmpRep, src, srcSize, 2 /*optLevel*/, ZSTD_noDict);   /* generate stats into ms->opt*/
        ZSTD_resetSeqStore(seqStore);
        /* invalidate first scan from history */
        ms->window.base -= srcSize;
        ms->window.dictLimit += (U32)srcSize;
        ms->window.lowLimit = ms->window.dictLimit;
        ms->nextToUpdate = ms->window.dictLimit;
        ms->nextToUpdate3 = ms->window.dictLimit;
        /* re-inforce weight of collected statistics */
        ZSTD_upscaleStats(&ms->opt);
    }
#endif
    return ZSTD_compressBlock_opt_generic(ms, seqStore, rep, src, srcSize, 2 /*optLevel*/, ZSTD_noDict);
}