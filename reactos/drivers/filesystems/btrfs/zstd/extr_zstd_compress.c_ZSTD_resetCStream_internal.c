#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
struct TYPE_8__ {int inBuffTarget; int blockSize; scalar_t__ frameEnded; int /*<<< orphan*/  streamStage; scalar_t__ outBuffFlushedSize; scalar_t__ outBuffContentSize; scalar_t__ inBuffPos; scalar_t__ inToCompress; } ;
typedef  TYPE_1__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_9__ {int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_compressBegin_internal (TYPE_1__*,void const* const,size_t const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,TYPE_2__,unsigned long long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_dtlm_fast ; 
 int /*<<< orphan*/  ZSTD_getCParamsFromCCtxParams (TYPE_2__*,unsigned long long const,size_t const) ; 
 int /*<<< orphan*/  ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDb_buffered ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  zcss_load ; 

__attribute__((used)) static size_t ZSTD_resetCStream_internal(ZSTD_CStream* cctx,
                    const void* const dict, size_t const dictSize, ZSTD_dictContentType_e const dictContentType,
                    const ZSTD_CDict* const cdict,
                    ZSTD_CCtx_params params, unsigned long long const pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_resetCStream_internal");
    /* Finalize the compression parameters */
    params.cParams = ZSTD_getCParamsFromCCtxParams(&params, pledgedSrcSize, dictSize);
    /* params are supposed to be fully validated at this point */
    assert(!ZSTD_isError(ZSTD_checkCParams(params.cParams)));
    assert(!((dict) && (cdict)));  /* either dict or cdict, not both */

    CHECK_F( ZSTD_compressBegin_internal(cctx,
                                         dict, dictSize, dictContentType, ZSTD_dtlm_fast,
                                         cdict,
                                         params, pledgedSrcSize,
                                         ZSTDb_buffered) );

    cctx->inToCompress = 0;
    cctx->inBuffPos = 0;
    cctx->inBuffTarget = cctx->blockSize
                      + (cctx->blockSize == pledgedSrcSize);   /* for small input: avoid automatic flush on reaching end of block, since it would require to add a 3-bytes null block to end frame */
    cctx->outBuffContentSize = cctx->outBuffFlushedSize = 0;
    cctx->streamStage = zcss_load;
    cctx->frameEnded = 0;
    return 0;   /* ready to go */
}