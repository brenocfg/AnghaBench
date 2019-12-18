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
struct MPContext {scalar_t__ video_status; double last_idle_tick; scalar_t__ paused; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_TICK ; 
 scalar_t__ STATUS_DRAINING ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double mp_time_sec () ; 

__attribute__((used)) static void handle_dummy_ticks(struct MPContext *mpctx)
{
    if ((mpctx->video_status != STATUS_PLAYING &&
         mpctx->video_status != STATUS_DRAINING) ||
         mpctx->paused)
    {
        if (mp_time_sec() - mpctx->last_idle_tick > 0.050) {
            mpctx->last_idle_tick = mp_time_sec();
            mp_notify(mpctx, MPV_EVENT_TICK, NULL);
        }
    }
}