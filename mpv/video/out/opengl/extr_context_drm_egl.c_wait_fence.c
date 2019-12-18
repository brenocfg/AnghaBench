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
struct ra_ctx {struct priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* DeleteSync ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ClientWaitSync ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {scalar_t__ num_bos; } ;
struct priv {scalar_t__ num_vsync_fences; int /*<<< orphan*/ * vsync_fences; TYPE_2__ gl; TYPE_1__ gbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SYNC_FLUSH_COMMANDS_BIT ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_fence(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    while (p->num_vsync_fences && (p->num_vsync_fences >= p->gbm.num_bos)) {
        p->gl.ClientWaitSync(p->vsync_fences[0], GL_SYNC_FLUSH_COMMANDS_BIT, 1e9);
        p->gl.DeleteSync(p->vsync_fences[0]);
        MP_TARRAY_REMOVE_AT(p->vsync_fences, p->num_vsync_fences, 0);
    }
}