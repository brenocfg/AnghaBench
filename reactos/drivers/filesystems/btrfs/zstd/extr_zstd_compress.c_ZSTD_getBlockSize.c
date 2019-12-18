#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int windowLog; } ;
typedef  TYPE_2__ ZSTD_compressionParameters ;
struct TYPE_6__ {TYPE_2__ cParams; } ;
struct TYPE_8__ {TYPE_1__ appliedParams; } ;
typedef  TYPE_3__ ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_MAX ; 
 int /*<<< orphan*/  ZSTD_checkCParams (TYPE_2__ const) ; 
 int /*<<< orphan*/  assert (int) ; 

size_t ZSTD_getBlockSize(const ZSTD_CCtx* cctx)
{
    ZSTD_compressionParameters const cParams = cctx->appliedParams.cParams;
    assert(!ZSTD_checkCParams(cParams));
    return MIN (ZSTD_BLOCKSIZE_MAX, (U32)1 << cParams.windowLog);
}