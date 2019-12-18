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
struct TYPE_3__ {scalar_t__ staticSize; int /*<<< orphan*/ * mtctx; int /*<<< orphan*/ * cdictLocal; int /*<<< orphan*/ * workSpace; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDMT_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void ZSTD_freeCCtxContent(ZSTD_CCtx* cctx)
{
    assert(cctx != NULL);
    assert(cctx->staticSize == 0);
    ZSTD_free(cctx->workSpace, cctx->customMem); cctx->workSpace = NULL;
    ZSTD_freeCDict(cctx->cdictLocal); cctx->cdictLocal = NULL;
#ifdef ZSTD_MULTITHREAD
    ZSTDMT_freeCCtx(cctx->mtctx); cctx->mtctx = NULL;
#endif
}