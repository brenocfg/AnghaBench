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
struct TYPE_11__ {int /*<<< orphan*/  control_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  video_wait; int /*<<< orphan*/  update_cond; struct TYPE_11__* dispatch; struct TYPE_11__* dr; struct TYPE_11__* renderer; struct TYPE_11__* priv; TYPE_1__* fns; int /*<<< orphan*/  vo; int /*<<< orphan*/  in_use; int /*<<< orphan*/  client_api; } ;
typedef  TYPE_2__ mpv_render_context ;
struct TYPE_10__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dr_helper_acquire_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  forget_frames (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kill_video_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_dispatch_queue_process (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_main_render_context (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
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

    if (atomic_load(&ctx->in_use)) {
        // Start destroy the VO, and also bring down the decoder etc., which
        // still might be using the hwdec context or use DR images. The above
        // mp_set_main_render_context() call guarantees it can't come back (so
        // ctx->vo can't change to non-NULL).
        // In theory, this races with vo_libmpv exiting and another VO being
        // used, which is a harmless grotesque corner case.
        kill_video_async(ctx->client_api);

        while (atomic_load(&ctx->in_use)) {
            // As a nasty detail, we need to wait until the VO is released, but
            // also need to react to update() calls during it (the update calls
            // are supposed to trigger processing ctx->dispatch). We solve this
            // by making the VO uninit function call mp_dispatch_interrupt().
            //
            // Other than that, processing ctx->dispatch is needed to serve the
            // video decoder, which might still not be fully destroyed, and e.g.
            // performs calls to release DR images (or, as a grotesque corner
            // case may even try to allocate new ones).
            //
            // Once the VO is released, ctx->dispatch becomes truly inactive.
            // (The libmpv API user could call mpv_render_context_update() while
            // mpv_render_context_free() is being called, but of course this is
            // invalid.)
            mp_dispatch_queue_process(ctx->dispatch, INFINITY);
        }
    }

    pthread_mutex_lock(&ctx->lock);
    // Barrier - guarantee uninit() has left the lock region. It will access ctx
    // until the lock has been released, so we must not proceed with destruction
    // before we can acquire the lock. (The opposite, uninit() acquiring the
    // lock, can not happen anymore at this point - we've waited for VO uninit,
    // and prevented that new VOs can be created.)
    pthread_mutex_unlock(&ctx->lock);

    assert(!atomic_load(&ctx->in_use));
    assert(!ctx->vo);

    // With the dispatch queue not being served anymore, allow frame free
    // requests from this thread to be served directly.
    if (ctx->dr)
        dr_helper_acquire_thread(ctx->dr);

    // Possibly remaining outstanding work.
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