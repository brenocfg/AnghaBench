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
struct vo_internal {scalar_t__ wakeup_pts; int want_redraw; int request_redraw; int send_reset; int paused; int /*<<< orphan*/  dr_helper; int /*<<< orphan*/ * current_frame; int /*<<< orphan*/  lock; scalar_t__ terminate; int /*<<< orphan*/  dispatch; } ;
struct vo {int want_redraw; TYPE_1__* driver; struct vo_internal* in; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit ) (struct vo*) ;int /*<<< orphan*/  (* control ) (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* preinit ) (struct vo*) ;scalar_t__ get_image; } ;

/* Variables and functions */
 scalar_t__ MPMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOCTRL_CHECK_EVENTS ; 
 int /*<<< orphan*/  VOCTRL_PAUSE ; 
 int /*<<< orphan*/  VOCTRL_RESET ; 
 int /*<<< orphan*/  VOCTRL_RESUME ; 
 int /*<<< orphan*/  VO_EVENT_WIN_STATE ; 
 int /*<<< orphan*/  do_redraw (struct vo*) ; 
 int /*<<< orphan*/  dr_helper_acquire_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_helper_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vo*) ; 
 int /*<<< orphan*/  forget_frames (struct vo*) ; 
 int /*<<< orphan*/  get_image_vo ; 
 int /*<<< orphan*/  mp_dispatch_queue_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_rendezvous (struct vo*,int) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_opts (struct vo*) ; 
 int render_frame (struct vo*) ; 
 scalar_t__ stub1 (struct vo*) ; 
 int /*<<< orphan*/  stub2 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (struct vo*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_display_fps (struct vo*) ; 
 int /*<<< orphan*/  vo_event (struct vo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_vo (struct vo*,scalar_t__) ; 
 int /*<<< orphan*/  wakeup_core (struct vo*) ; 

__attribute__((used)) static void *vo_thread(void *ptr)
{
    struct vo *vo = ptr;
    struct vo_internal *in = vo->in;
    bool vo_paused = false;

    mpthread_set_name("vo");

    if (vo->driver->get_image) {
        in->dr_helper = dr_helper_create(in->dispatch, get_image_vo, vo);
        dr_helper_acquire_thread(in->dr_helper);
    }

    int r = vo->driver->preinit(vo) ? -1 : 0;
    mp_rendezvous(vo, r); // init barrier
    if (r < 0)
        goto done;

    read_opts(vo);
    update_display_fps(vo);
    vo_event(vo, VO_EVENT_WIN_STATE);

    while (1) {
        mp_dispatch_queue_process(vo->in->dispatch, 0);
        if (in->terminate)
            break;
        vo->driver->control(vo, VOCTRL_CHECK_EVENTS, NULL);
        bool working = render_frame(vo);
        int64_t now = mp_time_us();
        int64_t wait_until = now + (working ? 0 : (int64_t)1e9);

        pthread_mutex_lock(&in->lock);
        if (in->wakeup_pts) {
            if (in->wakeup_pts > now) {
                wait_until = MPMIN(wait_until, in->wakeup_pts);
            } else {
                in->wakeup_pts = 0;
                wakeup_core(vo);
            }
        }
        if (vo->want_redraw && !in->want_redraw) {
            vo->want_redraw = false;
            in->want_redraw = true;
            wakeup_core(vo);
        }
        bool redraw = in->request_redraw;
        bool send_reset = in->send_reset;
        in->send_reset = false;
        bool send_pause = in->paused != vo_paused;
        vo_paused = in->paused;
        pthread_mutex_unlock(&in->lock);

        if (send_reset)
            vo->driver->control(vo, VOCTRL_RESET, NULL);
        if (send_pause)
            vo->driver->control(vo, vo_paused ? VOCTRL_PAUSE : VOCTRL_RESUME, NULL);
        if (wait_until > now && redraw) {
            do_redraw(vo); // now is a good time
            continue;
        }
        if (vo->want_redraw) // might have been set by VOCTRLs
            wait_until = 0;

        wait_vo(vo, wait_until);
    }
    forget_frames(vo); // implicitly synchronized
    talloc_free(in->current_frame);
    in->current_frame = NULL;
    vo->driver->uninit(vo);
done:
    TA_FREEP(&in->dr_helper);
    return NULL;
}