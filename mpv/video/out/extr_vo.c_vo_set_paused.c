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
struct vo_internal {int paused; int request_redraw; int /*<<< orphan*/  lock; scalar_t__ dropped_frame; } ;
struct vo {struct vo_internal* in; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_vsync_timings (struct vo*) ; 
 int /*<<< orphan*/  wakeup_core (struct vo*) ; 
 int /*<<< orphan*/  wakeup_locked (struct vo*) ; 

void vo_set_paused(struct vo *vo, bool paused)
{
    struct vo_internal *in = vo->in;
    pthread_mutex_lock(&in->lock);
    if (in->paused != paused) {
        in->paused = paused;
        if (in->paused && in->dropped_frame) {
            in->request_redraw = true;
            wakeup_core(vo);
        }
        reset_vsync_timings(vo);
        wakeup_locked(vo);
    }
    pthread_mutex_unlock(&in->lock);
}