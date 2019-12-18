#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cctxParams ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
struct TYPE_5__ {int contentSizeFlag; } ;
struct TYPE_6__ {TYPE_1__ fParams; int /*<<< orphan*/  compressionLevel; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ZSTD_CCtx_params ZSTD_makeCCtxParamsFromCParams(
        ZSTD_compressionParameters cParams)
{
    ZSTD_CCtx_params cctxParams;
    memset(&cctxParams, 0, sizeof(cctxParams));
    cctxParams.cParams = cParams;
    cctxParams.compressionLevel = ZSTD_CLEVEL_DEFAULT;  /* should not matter, as all cParams are presumed properly defined */
    assert(!ZSTD_checkCParams(cParams));
    cctxParams.fParams.contentSizeFlag = 1;
    return cctxParams;
}