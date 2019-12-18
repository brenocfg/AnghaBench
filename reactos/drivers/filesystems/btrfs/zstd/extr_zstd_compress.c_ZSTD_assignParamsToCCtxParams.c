#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cParams; int /*<<< orphan*/  fParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;
struct TYPE_7__ {int /*<<< orphan*/  compressionLevel; int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static ZSTD_CCtx_params ZSTD_assignParamsToCCtxParams(
        ZSTD_CCtx_params cctxParams, ZSTD_parameters params)
{
    ZSTD_CCtx_params ret = cctxParams;
    ret.cParams = params.cParams;
    ret.fParams = params.fParams;
    ret.compressionLevel = ZSTD_CLEVEL_DEFAULT;   /* should not matter, as all cParams are presumed properly defined */
    assert(!ZSTD_checkCParams(params.cParams));
    return ret;
}