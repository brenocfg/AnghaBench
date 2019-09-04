#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo_internal {int internal_events; double reported_display_fps; double display_fps; int nominal_vsync_interval; int queued_events; int /*<<< orphan*/  lock; int /*<<< orphan*/  vsync_interval; } ;
struct vo {TYPE_2__* opts; TYPE_1__* driver; struct vo_internal* in; } ;
struct TYPE_4__ {double override_display_fps; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* control ) (struct vo*,int /*<<< orphan*/ ,double*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPMAX (int,int) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,double) ; 
 int /*<<< orphan*/  VOCTRL_GET_DISPLAY_FPS ; 
 int VO_EVENT_WIN_STATE ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vo*,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  wakeup_core (struct vo*) ; 

__attribute__((used)) static void update_display_fps(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    pthread_mutex_lock(&in->lock);
    if (in->internal_events & VO_EVENT_WIN_STATE) {
        in->internal_events &= ~(unsigned)VO_EVENT_WIN_STATE;

        pthread_mutex_unlock(&in->lock);

        double fps = 0;
        vo->driver->control(vo, VOCTRL_GET_DISPLAY_FPS, &fps);

        pthread_mutex_lock(&in->lock);

        in->reported_display_fps = fps;
    }

    double display_fps = vo->opts->override_display_fps;
    if (display_fps <= 0)
        display_fps = in->reported_display_fps;

    if (in->display_fps != display_fps) {
        in->nominal_vsync_interval =  display_fps > 0 ? 1e6 / display_fps : 0;
        in->vsync_interval = MPMAX(in->nominal_vsync_interval, 1);
        in->display_fps = display_fps;

        MP_VERBOSE(vo, "Assuming %f FPS for display sync.\n", display_fps);

        // make sure to update the player
        in->queued_events |= VO_EVENT_WIN_STATE;
        wakeup_core(vo);
    }

    pthread_mutex_unlock(&in->lock);
}