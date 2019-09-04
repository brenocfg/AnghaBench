#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; struct cuda_mapper_priv* priv; TYPE_1__* owner; } ;
struct ext_vk {int /*<<< orphan*/  ws; int /*<<< orphan*/  sync; int /*<<< orphan*/  pltex; } ;
struct cuda_mapper_priv {struct ext_vk** ext; } ;
struct cuda_hw_priv {TYPE_2__* cu; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cuWaitExternalSemaphoresAsync ) (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct cuda_hw_priv* priv; } ;
typedef  TYPE_2__ CudaFunctions ;
typedef  TYPE_3__ CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int pl_tex_export (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_pl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cuda_ext_vk_wait(const struct ra_hwdec_mapper *mapper, int n)
{
    struct cuda_hw_priv *p_owner = mapper->owner->priv;
    struct cuda_mapper_priv *p = mapper->priv;
    CudaFunctions *cu = p_owner->cu;
    int ret;
    struct ext_vk *evk = p->ext[n];

    ret = pl_tex_export(ra_pl_get(mapper->ra),
                        evk->pltex, evk->sync);
    if (!ret)
        return false;

    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS wp = { 0, };
    ret = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(&evk->ws,
                                                     &wp, 1, 0));
    return ret == 0;
}