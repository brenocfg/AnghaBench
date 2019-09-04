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
struct vo_priv {struct mpv_render_context* ctx; } ;
struct vo_frame {int /*<<< orphan*/  current; scalar_t__ redraw; } ;
struct vo {struct vo_priv* priv; } ;
struct mpv_render_context {int redrawing; int /*<<< orphan*/  lock; scalar_t__ flip_count; scalar_t__ expected_flip_count; scalar_t__ next_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update (struct mpv_render_context*) ; 
 scalar_t__ vo_frame_ref (struct vo_frame*) ; 

__attribute__((used)) static void draw_frame(struct vo *vo, struct vo_frame *frame)
{
    struct vo_priv *p = vo->priv;
    struct mpv_render_context *ctx = p->ctx;

    pthread_mutex_lock(&ctx->lock);
    assert(!ctx->next_frame);
    ctx->next_frame = vo_frame_ref(frame);
    ctx->expected_flip_count = ctx->flip_count + 1;
    ctx->redrawing = frame->redraw || !frame->current;
    pthread_mutex_unlock(&ctx->lock);

    update(ctx);
}