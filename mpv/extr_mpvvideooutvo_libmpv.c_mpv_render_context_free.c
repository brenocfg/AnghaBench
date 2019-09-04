#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int had_kill_update; int /*<<< orphan*/  control_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  video_wait; int /*<<< orphan*/  update_cond; struct TYPE_11__* dispatch; struct TYPE_11__* dr; struct TYPE_11__* renderer; struct TYPE_11__* priv; TYPE_1__* fns; int /*<<< orphan*/  vo; int /*<<< orphan*/  in_use; int /*<<< orphan*/  client_api; } ;
typedef  TYPE_2__ mpv_render_context ;
struct TYPE_10__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forget_frames (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kill_cb ; 
 int /*<<< orphan*/  kill_video_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mp_dispatch_queue_process (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_main_render_context (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__*) ; 

void mpv_render_context_free(mpv_render_context *ctx)
{
    if (!ctx)
        return;

    // From here on, ctx becomes invisible and cannot be newly acquired. Only
    // a VO could still hold a reference.
    mp_set_main_render_context(ctx->client_api, ctx, false);

    // If it's still in use, a VO using it must be active. Destroy the VO, and
    // also bring down the decoder etc., which still might be using the hwdec
    // context. The above removal guarantees it can't come back (so ctx->vo
    // can't change to non-NULL).
    if (atomic_load(&ctx->in_use)) {
        kill_video_async(ctx->client_api, kill_cb, ctx);

        while (atomic_load(&ctx->in_use)) {
            // As long as the video decoders are not destroyed, they can still
            // try to allocate new DR images and so on. This is a grotesque
            // corner case, but possible. Also, more likely, DR images need to
            // be released while the video chain is destroyed.
            if (ctx->dispatch)
                mp_dispatch_queue_process(ctx->dispatch, 0);

            // Wait for kill_cb() or update() calls.
            pthread_mutex_lock(&ctx->update_lock);
            if (!ctx->had_kill_update)
                pthread_cond_wait(&ctx->update_cond, &ctx->update_lock);
            ctx->had_kill_update = false;
            pthread_mutex_unlock(&ctx->update_lock);
        }
    }

    assert(!atomic_load(&ctx->in_use));
    assert(!ctx->vo);

    // Possibly remaining outstanding work.
    if (ctx->dispatch)
        mp_dispatch_queue_process(ctx->dispatch, 0);

    forget_frames(ctx, true);

    if (ctx->renderer) {
        ctx->renderer->fns->destroy(ctx->renderer);
        talloc_free(ctx->renderer->priv);
        talloc_free(ctx->renderer);
    }
    talloc_free(ctx->dr);
    talloc_free(ctx->dispatch);

    pthread_cond_destroy(&ctx->update_cond);
    pthread_cond_destroy(&ctx->video_wait);
    pthread_mutex_destroy(&ctx->update_lock);
    pthread_mutex_destroy(&ctx->lock);
    pthread_mutex_destroy(&ctx->control_lock);

    talloc_free(ctx);
}