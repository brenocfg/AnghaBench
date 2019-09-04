#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flip_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  video_wait; } ;
typedef  TYPE_1__ mpv_render_context ;

/* Variables and functions */
 int /*<<< orphan*/  MP_STATS (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mpv_render_context_report_swap(mpv_render_context *ctx)
{
    MP_STATS(ctx, "glcb-reportflip");

    pthread_mutex_lock(&ctx->lock);
    ctx->flip_count += 1;
    pthread_cond_broadcast(&ctx->video_wait);
    pthread_mutex_unlock(&ctx->lock);
}