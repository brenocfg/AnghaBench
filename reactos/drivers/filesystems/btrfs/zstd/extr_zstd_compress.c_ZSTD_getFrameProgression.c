#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nbActiveWorkers; scalar_t__ currentJobID; int /*<<< orphan*/  flushed; int /*<<< orphan*/  produced; scalar_t__ consumed; scalar_t__ ingested; } ;
typedef  TYPE_2__ ZSTD_frameProgression ;
struct TYPE_7__ {scalar_t__ nbWorkers; } ;
struct TYPE_9__ {size_t inBuffPos; size_t inToCompress; int /*<<< orphan*/  producedCSize; scalar_t__ consumedSrcSize; int /*<<< orphan*/ * inBuff; int /*<<< orphan*/  mtctx; TYPE_1__ appliedParams; } ;
typedef  TYPE_3__ ZSTD_CCtx ;

/* Variables and functions */
 TYPE_2__ ZSTDMT_getFrameProgression (int /*<<< orphan*/ ) ; 
 size_t const ZSTD_BLOCKSIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

ZSTD_frameProgression ZSTD_getFrameProgression(const ZSTD_CCtx* cctx)
{
#ifdef ZSTD_MULTITHREAD
    if (cctx->appliedParams.nbWorkers > 0) {
        return ZSTDMT_getFrameProgression(cctx->mtctx);
    }
#endif
    {   ZSTD_frameProgression fp;
        size_t const buffered = (cctx->inBuff == NULL) ? 0 :
                                cctx->inBuffPos - cctx->inToCompress;
        if (buffered) assert(cctx->inBuffPos >= cctx->inToCompress);
        assert(buffered <= ZSTD_BLOCKSIZE_MAX);
        fp.ingested = cctx->consumedSrcSize + buffered;
        fp.consumed = cctx->consumedSrcSize;
        fp.produced = cctx->producedCSize;
        fp.flushed  = cctx->producedCSize;   /* simplified; some data might still be left within streaming output buffer */
        fp.currentJobID = 0;
        fp.nbActiveWorkers = 0;
        return fp;
}   }