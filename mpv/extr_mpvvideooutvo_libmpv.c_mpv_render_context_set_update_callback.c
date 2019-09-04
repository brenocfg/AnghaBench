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
typedef  int /*<<< orphan*/  (* mpv_render_update_fn ) (void*) ;
struct TYPE_3__ {int /*<<< orphan*/  update_lock; void* update_cb_ctx; int /*<<< orphan*/  (* update_cb ) (void*) ;} ;
typedef  TYPE_1__ mpv_render_context ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void mpv_render_context_set_update_callback(mpv_render_context *ctx,
                                            mpv_render_update_fn callback,
                                            void *callback_ctx)
{
    pthread_mutex_lock(&ctx->update_lock);
    ctx->update_cb = callback;
    ctx->update_cb_ctx = callback_ctx;
    if (ctx->update_cb)
        ctx->update_cb(ctx->update_cb_ctx);
    pthread_mutex_unlock(&ctx->update_lock);
}