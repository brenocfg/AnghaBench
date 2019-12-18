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
struct TYPE_7__ {int contentSizeFlag; } ;
struct TYPE_9__ {TYPE_1__ fParams; } ;
struct TYPE_8__ {int /*<<< orphan*/  cdict; TYPE_3__ requestedParams; } ;
typedef  TYPE_2__ ZSTD_CStream ;
typedef  TYPE_3__ ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 size_t ZSTD_resetCStream_internal (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__,unsigned long long) ; 

size_t ZSTD_resetCStream(ZSTD_CStream* zcs, unsigned long long pledgedSrcSize)
{
    ZSTD_CCtx_params params = zcs->requestedParams;
    DEBUGLOG(4, "ZSTD_resetCStream: pledgedSrcSize = %u", (U32)pledgedSrcSize);
    if (pledgedSrcSize==0) pledgedSrcSize = ZSTD_CONTENTSIZE_UNKNOWN;
    params.fParams.contentSizeFlag = 1;
    return ZSTD_resetCStream_internal(zcs, NULL, 0, ZSTD_dct_auto, zcs->cdict, params, pledgedSrcSize);
}