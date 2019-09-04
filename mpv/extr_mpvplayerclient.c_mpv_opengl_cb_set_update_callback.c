#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpv_opengl_cb_update_fn ;
struct TYPE_5__ {void* callback_ctx; int /*<<< orphan*/  callback; TYPE_1__* client_api; } ;
typedef  TYPE_2__ mpv_opengl_cb_context ;
struct TYPE_4__ {scalar_t__ render_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpv_render_context_set_update_callback (scalar_t__,int /*<<< orphan*/ ,void*) ; 

void mpv_opengl_cb_set_update_callback(mpv_opengl_cb_context *ctx,
                                       mpv_opengl_cb_update_fn callback,
                                       void *callback_ctx)
{
    // This was probably supposed to be thread-safe, but we don't care. It's
    // compatibility code, and if you have problems, use the new API.
    if (ctx->client_api->render_context) {
        mpv_render_context_set_update_callback(ctx->client_api->render_context,
                                               callback, callback_ctx);
    }
    // Nasty thing: could set this even while not initialized, so we need to
    // preserve it.
    ctx->callback = callback;
    ctx->callback_ctx = callback_ctx;
}