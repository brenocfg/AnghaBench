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
struct MPContext {int /*<<< orphan*/ * video_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_VIDEO_RECONFIG ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninit_video_chain (struct MPContext*) ; 
 int /*<<< orphan*/  vo_destroy (int /*<<< orphan*/ *) ; 

void uninit_video_out(struct MPContext *mpctx)
{
    uninit_video_chain(mpctx);
    if (mpctx->video_out) {
        vo_destroy(mpctx->video_out);
        mp_notify(mpctx, MPV_EVENT_VIDEO_RECONFIG, NULL);
    }
    mpctx->video_out = NULL;
}