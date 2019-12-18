#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mpv_render_context {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  update_cond; int /*<<< orphan*/  update_cb_ctx; int /*<<< orphan*/  (* update_cb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update(struct mpv_render_context *ctx)
{
    pthread_mutex_lock(&ctx->update_lock);
    if (ctx->update_cb)
        ctx->update_cb(ctx->update_cb_ctx);

    pthread_cond_broadcast(&ctx->update_cond);
    pthread_mutex_unlock(&ctx->update_lock);
}