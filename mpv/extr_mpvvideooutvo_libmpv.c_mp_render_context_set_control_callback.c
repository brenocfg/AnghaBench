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
struct TYPE_3__ {int /*<<< orphan*/  control_lock; void* control_cb_ctx; int /*<<< orphan*/  control_cb; } ;
typedef  TYPE_1__ mpv_render_context ;
typedef  int /*<<< orphan*/  mp_render_cb_control_fn ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_render_context_set_control_callback(mpv_render_context *ctx,
                                            mp_render_cb_control_fn callback,
                                            void *callback_ctx)
{
    pthread_mutex_lock(&ctx->control_lock);
    ctx->control_cb = callback;
    ctx->control_cb_ctx = callback_ctx;
    pthread_mutex_unlock(&ctx->control_lock);
}