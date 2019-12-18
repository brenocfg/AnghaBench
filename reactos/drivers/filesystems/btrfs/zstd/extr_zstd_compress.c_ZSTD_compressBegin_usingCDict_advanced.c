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
typedef  int /*<<< orphan*/  ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_9__ {int /*<<< orphan*/  windowLog; } ;
struct TYPE_7__ {int /*<<< orphan*/  fParams; TYPE_3__ cParams; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;
struct TYPE_8__ {TYPE_1__ requestedParams; } ;
typedef  TYPE_2__ ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  MIN (unsigned long long const,unsigned int) ; 
 unsigned long long const ZSTD_CONTENTSIZE_UNKNOWN ; 
 size_t ZSTD_compressBegin_internal (TYPE_2__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,TYPE_1__,unsigned long long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 int /*<<< orphan*/  ZSTD_dtlm_fast ; 
 TYPE_3__ ZSTD_getCParamsFromCDict (int /*<<< orphan*/  const* const) ; 
 int ZSTD_highbit32 (int const) ; 
 int /*<<< orphan*/  ZSTDb_not_buffered ; 
 int /*<<< orphan*/  dictionary_wrong ; 

size_t ZSTD_compressBegin_usingCDict_advanced(
    ZSTD_CCtx* const cctx, const ZSTD_CDict* const cdict,
    ZSTD_frameParameters const fParams, unsigned long long const pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_compressBegin_usingCDict_advanced");
    if (cdict==NULL) return ERROR(dictionary_wrong);
    {   ZSTD_CCtx_params params = cctx->requestedParams;
        params.cParams = ZSTD_getCParamsFromCDict(cdict);
        /* Increase window log to fit the entire dictionary and source if the
         * source size is known. Limit the increase to 19, which is the
         * window log for compression level 1 with the largest source size.
         */
        if (pledgedSrcSize != ZSTD_CONTENTSIZE_UNKNOWN) {
            U32 const limitedSrcSize = (U32)MIN(pledgedSrcSize, 1U << 19);
            U32 const limitedSrcLog = limitedSrcSize > 1 ? ZSTD_highbit32(limitedSrcSize - 1) + 1 : 1;
            params.cParams.windowLog = MAX(params.cParams.windowLog, limitedSrcLog);
        }
        params.fParams = fParams;
        return ZSTD_compressBegin_internal(cctx,
                                           NULL, 0, ZSTD_dct_auto, ZSTD_dtlm_fast,
                                           cdict,
                                           params, pledgedSrcSize,
                                           ZSTDb_not_buffered);
    }
}