#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  customFree; int /*<<< orphan*/  customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 int /*<<< orphan*/  ZSTD_initCCtx (int /*<<< orphan*/ * const,TYPE_1__) ; 
 scalar_t__ ZSTD_malloc (int,TYPE_1__) ; 
 scalar_t__ zcss_init ; 

ZSTD_CCtx* ZSTD_createCCtx_advanced(ZSTD_customMem customMem)
{
    ZSTD_STATIC_ASSERT(zcss_init==0);
    ZSTD_STATIC_ASSERT(ZSTD_CONTENTSIZE_UNKNOWN==(0ULL - 1));
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;
    {   ZSTD_CCtx* const cctx = (ZSTD_CCtx*)ZSTD_malloc(sizeof(ZSTD_CCtx), customMem);
        if (!cctx) return NULL;
        ZSTD_initCCtx(cctx, customMem);
        return cctx;
    }
}