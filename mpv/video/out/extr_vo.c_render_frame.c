#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo_vsync_info {int last_queue_display_time; int skipped_vsyncs; } ;
struct vo_internal {scalar_t__ flip_queue_offset; int dropped_frame; scalar_t__ prev_vsync; int hasframe_rendered; int expecting_vsync; int drop_count; int rendering; int request_redraw; struct vo_frame* frame_queued; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; struct vo_frame* current_frame; scalar_t__ paused; int /*<<< orphan*/  hasframe; } ;
struct vo_frame {int num_vsyncs; scalar_t__ pts; int duration; int can_drop; int repeat; scalar_t__ display_synced; int /*<<< orphan*/  current; scalar_t__ vsync_interval; int /*<<< orphan*/  vsync_offset; } ;
struct vo {TYPE_1__* driver; struct vo_internal* in; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int caps; int /*<<< orphan*/  (* get_vsync ) (struct vo*,struct vo_vsync_info*) ;int /*<<< orphan*/  (* flip_page ) (struct vo*) ;int /*<<< orphan*/  (* draw_image ) (struct vo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* draw_frame ) (struct vo*,struct vo_frame*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_STATS (struct vo*,char*) ; 
 int VO_CAP_FRAMEDROP ; 
 int VO_CAP_NORETAIN ; 
 int /*<<< orphan*/  assert (struct vo_frame*) ; 
 int /*<<< orphan*/  mp_image_new_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vo*,struct vo_frame*) ; 
 int /*<<< orphan*/  stub2 (struct vo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct vo*) ; 
 int /*<<< orphan*/  stub4 (struct vo*,struct vo_vsync_info*) ; 
 int /*<<< orphan*/  talloc_free (struct vo_frame*) ; 
 int /*<<< orphan*/  update_display_fps (struct vo*) ; 
 int /*<<< orphan*/  update_vsync_timing_after_swap (struct vo*,struct vo_vsync_info*) ; 
 struct vo_frame* vo_frame_ref (struct vo_frame*) ; 
 int /*<<< orphan*/  wait_until (struct vo*,scalar_t__) ; 
 int /*<<< orphan*/  wakeup_core (struct vo*) ; 

__attribute__((used)) static bool render_frame(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    struct vo_frame *frame = NULL;
    bool got_frame = false;

    update_display_fps(vo);

    pthread_mutex_lock(&in->lock);

    if (in->frame_queued) {
        talloc_free(in->current_frame);
        in->current_frame = in->frame_queued;
        in->frame_queued = NULL;
    } else if (in->paused || !in->current_frame || !in->hasframe ||
               (in->current_frame->display_synced && in->current_frame->num_vsyncs < 1) ||
               !in->current_frame->display_synced)
    {
        goto done;
    }

    frame = vo_frame_ref(in->current_frame);
    assert(frame);

    if (frame->display_synced) {
        frame->pts = 0;
        frame->duration = -1;
    }

    int64_t now = mp_time_us();
    int64_t pts = frame->pts;
    int64_t duration = frame->duration;
    int64_t end_time = pts + duration;

    // Time at which we should flip_page on the VO.
    int64_t target = frame->display_synced ? 0 : pts - in->flip_queue_offset;

    // "normal" strict drop threshold.
    in->dropped_frame = duration >= 0 && end_time < now;

    in->dropped_frame &= !frame->display_synced;
    in->dropped_frame &= !(vo->driver->caps & VO_CAP_FRAMEDROP);
    in->dropped_frame &= frame->can_drop;
    // Even if we're hopelessly behind, rather degrade to 10 FPS playback,
    // instead of just freezing the display forever.
    in->dropped_frame &= now - in->prev_vsync < 100 * 1000;
    in->dropped_frame &= in->hasframe_rendered;

    // Setup parameters for the next time this frame is drawn. ("frame" is the
    // frame currently drawn, while in->current_frame is the potentially next.)
    in->current_frame->repeat = true;
    if (frame->display_synced) {
        in->current_frame->vsync_offset += in->current_frame->vsync_interval;
        in->dropped_frame |= in->current_frame->num_vsyncs < 1;
    }
    if (in->current_frame->num_vsyncs > 0)
        in->current_frame->num_vsyncs -= 1;

    bool use_vsync = in->current_frame->display_synced && !in->paused;
    if (use_vsync && !in->expecting_vsync) // first DS frame in a row
        in->prev_vsync = now;
    in->expecting_vsync = use_vsync;

    if (in->dropped_frame) {
        in->drop_count += 1;
    } else {
        in->rendering = true;
        in->hasframe_rendered = true;
        int64_t prev_drop_count = vo->in->drop_count;
        pthread_mutex_unlock(&in->lock);
        wakeup_core(vo); // core can queue new video now

        MP_STATS(vo, "start video-draw");

        if (vo->driver->draw_frame) {
            vo->driver->draw_frame(vo, frame);
        } else {
            vo->driver->draw_image(vo, mp_image_new_ref(frame->current));
        }

        MP_STATS(vo, "end video-draw");

        wait_until(vo, target);

        MP_STATS(vo, "start video-flip");

        vo->driver->flip_page(vo);

        struct vo_vsync_info vsync = {
            .last_queue_display_time = -1,
            .skipped_vsyncs = -1,
        };
        if (vo->driver->get_vsync)
            vo->driver->get_vsync(vo, &vsync);

        // Make up some crap if presentation feedback is missing.
        if (vsync.last_queue_display_time < 0)
            vsync.last_queue_display_time = mp_time_us();

        MP_STATS(vo, "end video-flip");

        pthread_mutex_lock(&in->lock);
        in->dropped_frame = prev_drop_count < vo->in->drop_count;
        in->rendering = false;

        update_vsync_timing_after_swap(vo, &vsync);
    }

    if (vo->driver->caps & VO_CAP_NORETAIN) {
        talloc_free(in->current_frame);
        in->current_frame = NULL;
    }

    if (in->dropped_frame) {
        MP_STATS(vo, "drop-vo");
    } else {
        in->request_redraw = false;
    }

    pthread_cond_broadcast(&in->wakeup); // for vo_wait_frame()
    wakeup_core(vo);

    got_frame = true;

done:
    talloc_free(frame);
    pthread_mutex_unlock(&in->lock);
    return got_frame || (in->frame_queued && in->frame_queued->display_synced);
}