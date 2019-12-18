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
struct TYPE_8__ {int /*<<< orphan*/  const* cdict; int /*<<< orphan*/  const* cdictLocal; int /*<<< orphan*/  customMem; scalar_t__ staticSize; } ;
typedef  TYPE_1__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_9__ {int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ZSTD_createCDict_advanced (void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 int /*<<< orphan*/  ZSTD_dlm_byCopy ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_getCParamsFromCCtxParams (TYPE_2__*,unsigned long long,size_t) ; 
 int /*<<< orphan*/  ZSTD_getCParamsFromCDict (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_isError (int /*<<< orphan*/ ) ; 
 size_t ZSTD_resetCStream_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__,unsigned long long) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTD_initCStream_internal(ZSTD_CStream* zcs,
                    const void* dict, size_t dictSize, const ZSTD_CDict* cdict,
                    ZSTD_CCtx_params params, unsigned long long pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_initCStream_internal");
    params.cParams = ZSTD_getCParamsFromCCtxParams(&params, pledgedSrcSize, dictSize);
    assert(!ZSTD_isError(ZSTD_checkCParams(params.cParams)));
    assert(!((dict) && (cdict)));  /* either dict or cdict, not both */

    if (dict && dictSize >= 8) {
        DEBUGLOG(4, "loading dictionary of size %u", (U32)dictSize);
        if (zcs->staticSize) {   /* static CCtx : never uses malloc */
            /* incompatible with internal cdict creation */
            return ERROR(memory_allocation);
        }
        ZSTD_freeCDict(zcs->cdictLocal);
        zcs->cdictLocal = ZSTD_createCDict_advanced(dict, dictSize,
                                            ZSTD_dlm_byCopy, ZSTD_dct_auto,
                                            params.cParams, zcs->customMem);
        zcs->cdict = zcs->cdictLocal;
        if (zcs->cdictLocal == NULL) return ERROR(memory_allocation);
    } else {
        if (cdict) {
            params.cParams = ZSTD_getCParamsFromCDict(cdict);  /* cParams are enforced from cdict; it includes windowLog */
        }
        ZSTD_freeCDict(zcs->cdictLocal);
        zcs->cdictLocal = NULL;
        zcs->cdict = cdict;
    }

    return ZSTD_resetCStream_internal(zcs, NULL, 0, ZSTD_dct_auto, zcs->cdict, params, pledgedSrcSize);
}