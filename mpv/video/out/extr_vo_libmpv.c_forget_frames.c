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
struct mpv_render_context {int /*<<< orphan*/ * cur_frame; int /*<<< orphan*/  video_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void forget_frames(struct mpv_render_context *ctx, bool all)
{
    pthread_cond_broadcast(&ctx->video_wait);
    if (all) {
        talloc_free(ctx->cur_frame);
        ctx->cur_frame = NULL;
    }
}