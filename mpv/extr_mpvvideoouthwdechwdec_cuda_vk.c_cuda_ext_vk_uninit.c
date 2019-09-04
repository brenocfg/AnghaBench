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
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; struct cuda_mapper_priv* priv; TYPE_1__* owner; } ;
struct ext_vk {int /*<<< orphan*/  sync; scalar_t__ ws; scalar_t__ ss; scalar_t__ mem; scalar_t__ mma; } ;
struct cuda_mapper_priv {struct ext_vk** ext; } ;
struct cuda_hw_priv {TYPE_2__* cu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cuDestroyExternalSemaphore ) (scalar_t__) ;int /*<<< orphan*/  (* cuDestroyExternalMemory ) (scalar_t__) ;int /*<<< orphan*/  (* cuMipmappedArrayDestroy ) (scalar_t__) ;} ;
struct TYPE_3__ {struct cuda_hw_priv* priv; } ;
typedef  TYPE_2__ CudaFunctions ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl_sync_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_pl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (struct ext_vk*) ; 

__attribute__((used)) static void cuda_ext_vk_uninit(const struct ra_hwdec_mapper *mapper, int n)
{
    struct cuda_hw_priv *p_owner = mapper->owner->priv;
    struct cuda_mapper_priv *p = mapper->priv;
    CudaFunctions *cu = p_owner->cu;

    struct ext_vk *evk = p->ext[n];
    if (evk) {
        if (evk->mma) {
            CHECK_CU(cu->cuMipmappedArrayDestroy(evk->mma));
            evk->mma = 0;
        }
        if (evk->mem) {
            CHECK_CU(cu->cuDestroyExternalMemory(evk->mem));
            evk->mem = 0;
        }
        if (evk->ss) {
            CHECK_CU(cu->cuDestroyExternalSemaphore(evk->ss));
            evk->ss = 0;
        }
        if (evk->ws) {
            CHECK_CU(cu->cuDestroyExternalSemaphore(evk->ws));
            evk->ws = 0;
        }
        pl_sync_destroy(ra_pl_get(mapper->ra), &evk->sync);
    }
    talloc_free(evk);
}