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
struct mpvk_ctx {int /*<<< orphan*/  pl_log; int /*<<< orphan*/  ctx; TYPE_1__* vkinst; int /*<<< orphan*/ * surface; } ;
struct TYPE_3__ {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  pl_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_vk_inst_destroy (TYPE_1__**) ; 
 int /*<<< orphan*/  vkDestroySurfaceKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void mpvk_uninit(struct mpvk_ctx *vk)
{
    if (vk->surface) {
        assert(vk->vkinst);
        vkDestroySurfaceKHR(vk->vkinst->instance, vk->surface, NULL);
        vk->surface = NULL;
    }

    pl_vk_inst_destroy(&vk->vkinst);
    pl_context_destroy(&vk->ctx);
    TA_FREEP(&vk->pl_log);
}