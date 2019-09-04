#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {struct priv* priv; } ;
struct TYPE_2__ {scalar_t__ (* FenceSync ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct priv {int /*<<< orphan*/  num_vsync_fences; int /*<<< orphan*/  vsync_fences; TYPE_1__ gl; } ;
typedef  scalar_t__ GLsync ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SYNC_GPU_COMMANDS_COMPLETE ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_fence(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    if (p->gl.FenceSync) {
        GLsync fence = p->gl.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        if (fence)
            MP_TARRAY_APPEND(p, p->vsync_fences, p->num_vsync_fences, fence);
    }
}