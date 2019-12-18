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
struct MPContext {int /*<<< orphan*/  video_out; TYPE_1__* opts; int /*<<< orphan*/  playback_active; } ;
struct TYPE_2__ {int /*<<< orphan*/  stop_screensaver; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_KILL_SCREENSAVER ; 
 int /*<<< orphan*/  VOCTRL_RESTORE_SCREENSAVER ; 
 int /*<<< orphan*/  vo_control_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void update_screensaver_state(struct MPContext *mpctx)
{
    if (!mpctx->video_out)
        return;

    bool saver_state = !mpctx->playback_active || !mpctx->opts->stop_screensaver;
    vo_control_async(mpctx->video_out, saver_state ? VOCTRL_RESTORE_SCREENSAVER
                                                   : VOCTRL_KILL_SCREENSAVER, NULL);
}