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
struct MPContext {int /*<<< orphan*/  video_status; int /*<<< orphan*/ * vo_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_VIDEO_RECONFIG ; 
 int /*<<< orphan*/  STATUS_EOF ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_video_state (struct MPContext*) ; 
 int /*<<< orphan*/  vo_chain_uninit (int /*<<< orphan*/ *) ; 

void uninit_video_chain(struct MPContext *mpctx)
{
    if (mpctx->vo_chain) {
        reset_video_state(mpctx);
        vo_chain_uninit(mpctx->vo_chain);
        mpctx->vo_chain = NULL;

        mpctx->video_status = STATUS_EOF;

        mp_notify(mpctx, MPV_EVENT_VIDEO_RECONFIG, NULL);
    }
}