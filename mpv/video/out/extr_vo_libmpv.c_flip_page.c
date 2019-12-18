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
struct vo {struct vo_priv* priv; } ;
struct timespec {int dummy; } ;
struct mpv_render_context {int present_count; scalar_t__ expected_flip_count; scalar_t__ flip_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  video_wait; int /*<<< orphan*/ * next_frame; int /*<<< orphan*/ * cur_frame; scalar_t__ redrawing; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*) ; 
 struct timespec mp_rel_time_to_timespec (double) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vo_increment_drop_count (struct vo*,int) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct vo_priv *p = vo->priv;
    struct mpv_render_context *ctx = p->ctx;
    struct timespec ts = mp_rel_time_to_timespec(0.2);

    pthread_mutex_lock(&ctx->lock);

    // Wait until frame was rendered
    while (ctx->next_frame) {
        if (pthread_cond_timedwait(&ctx->video_wait, &ctx->lock, &ts)) {
            if (ctx->next_frame) {
                MP_VERBOSE(vo, "mpv_render_context_render() not being called "
                           "or stuck.\n");
                goto done;
            }
        }
    }

    // Unblock mpv_render_context_render().
    ctx->present_count += 1;
    pthread_cond_broadcast(&ctx->video_wait);

    if (ctx->redrawing)
        goto done; // do not block for redrawing

    // Wait until frame was presented
    while (ctx->expected_flip_count > ctx->flip_count) {
        // mpv_render_report_swap() is declared as optional API.
        // Assume the user calls it consistently _if_ it's called at all.
        if (!ctx->flip_count)
            break;
        if (pthread_cond_timedwait(&ctx->video_wait, &ctx->lock, &ts)) {
            MP_VERBOSE(vo, "mpv_render_report_swap() not being called.\n");
            goto done;
        }
    }

done:

    // Cleanup after the API user is not reacting, or is being unusually slow.
    if (ctx->next_frame) {
        talloc_free(ctx->cur_frame);
        ctx->cur_frame = ctx->next_frame;
        ctx->next_frame = NULL;
        ctx->present_count += 2;
        pthread_cond_signal(&ctx->video_wait);
        vo_increment_drop_count(vo, 1);
    }

    pthread_mutex_unlock(&ctx->lock);
}