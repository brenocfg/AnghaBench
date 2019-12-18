#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ra_swapchain {struct ra_ctx* ctx; } ;
struct ra_ctx {TYPE_5__* vo; struct priv* priv; } ;
struct TYPE_8__ {int num_bos; TYPE_4__** bo_queue; int /*<<< orphan*/  surface; } ;
struct TYPE_6__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  display; } ;
struct priv {TYPE_3__ gbm; scalar_t__ waiting_for_flip; TYPE_1__ egl; int /*<<< orphan*/  active; scalar_t__ still; scalar_t__ paused; } ;
struct gbm_bo {int dummy; } ;
struct TYPE_10__ {TYPE_2__* opts; } ;
struct TYPE_9__ {int /*<<< orphan*/  bo; } ;
struct TYPE_7__ {int swapchain_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_bo (struct ra_ctx*,struct gbm_bo*) ; 
 int /*<<< orphan*/  gbm_surface_has_free_buffers (int /*<<< orphan*/ ) ; 
 struct gbm_bo* gbm_surface_lock_front_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_fence (struct ra_ctx*) ; 
 int /*<<< orphan*/  queue_flip (struct ra_ctx*,TYPE_4__*) ; 
 int /*<<< orphan*/  swapchain_step (struct ra_ctx*) ; 
 int /*<<< orphan*/  wait_fence (struct ra_ctx*) ; 
 int /*<<< orphan*/  wait_on_flip (struct ra_ctx*) ; 

__attribute__((used)) static void drm_egl_swap_buffers(struct ra_swapchain *sw)
{
    struct ra_ctx *ctx = sw->ctx;
    struct priv *p = ctx->priv;
    const bool drain = p->paused || p->still;  // True when we need to drain the swapchain

    if (!p->active)
        return;

    wait_fence(ctx);

    eglSwapBuffers(p->egl.display, p->egl.surface);

    struct gbm_bo *new_bo = gbm_surface_lock_front_buffer(p->gbm.surface);
    if (!new_bo) {
        MP_ERR(ctx->vo, "Couldn't lock front buffer\n");
        return;
    }
    enqueue_bo(ctx, new_bo);
    new_fence(ctx);

    while (drain || p->gbm.num_bos > ctx->vo->opts->swapchain_depth ||
           !gbm_surface_has_free_buffers(p->gbm.surface)) {
        if (p->waiting_for_flip) {
            wait_on_flip(ctx);
            swapchain_step(ctx);
        }
        if (p->gbm.num_bos <= 1)
            break;
        if (!p->gbm.bo_queue[1] || !p->gbm.bo_queue[1]->bo) {
            MP_ERR(ctx->vo, "Hole in swapchain?\n");
            swapchain_step(ctx);
            continue;
        }
        queue_flip(ctx, p->gbm.bo_queue[1]);
    }
}