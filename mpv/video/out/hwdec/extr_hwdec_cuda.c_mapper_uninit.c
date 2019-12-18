#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec_mapper {int /*<<< orphan*/ * tex; int /*<<< orphan*/  ra; TYPE_1__* owner; struct cuda_mapper_priv* priv; } ;
struct cuda_mapper_priv {int /*<<< orphan*/  display_ctx; } ;
struct cuda_hw_priv {int /*<<< orphan*/  (* ext_uninit ) (struct ra_hwdec_mapper*,int) ;TYPE_2__* cu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuCtxPushCurrent ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct cuda_hw_priv* priv; } ;
typedef  TYPE_2__ CudaFunctions ;
typedef  int /*<<< orphan*/  CUcontext ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ra_hwdec_mapper*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mapper_uninit(struct ra_hwdec_mapper *mapper)
{
    struct cuda_mapper_priv *p = mapper->priv;
    struct cuda_hw_priv *p_owner = mapper->owner->priv;
    CudaFunctions *cu = p_owner->cu;
    CUcontext dummy;

    // Don't bail if any CUDA calls fail. This is all best effort.
    CHECK_CU(cu->cuCtxPushCurrent(p->display_ctx));
    for (int n = 0; n < 4; n++) {
        p_owner->ext_uninit(mapper, n);
        ra_tex_free(mapper->ra, &mapper->tex[n]);
    }
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
}