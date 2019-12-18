#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ contentSizeFlag; } ;
struct TYPE_9__ {TYPE_1__ fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_parameters ;
struct TYPE_10__ {int /*<<< orphan*/  requestedParams; } ;
typedef  TYPE_3__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_assignParamsToCCtxParams (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 size_t ZSTD_initCStream_internal (TYPE_3__*,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long) ; 

size_t ZSTD_initCStream_advanced(ZSTD_CStream* zcs,
                                 const void* dict, size_t dictSize,
                                 ZSTD_parameters params, unsigned long long pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_initCStream_advanced: pledgedSrcSize=%u, flag=%u",
                (U32)pledgedSrcSize, params.fParams.contentSizeFlag);
    CHECK_F( ZSTD_checkCParams(params.cParams) );
    if ((pledgedSrcSize==0) && (params.fParams.contentSizeFlag==0)) pledgedSrcSize = ZSTD_CONTENTSIZE_UNKNOWN;  /* for compatibility with older programs relying on this behavior. Users should now specify ZSTD_CONTENTSIZE_UNKNOWN. This line will be removed in the future. */
    zcs->requestedParams = ZSTD_assignParamsToCCtxParams(zcs->requestedParams, params);
    return ZSTD_initCStream_internal(zcs, dict, dictSize, NULL /*cdict*/, zcs->requestedParams, pledgedSrcSize);
}