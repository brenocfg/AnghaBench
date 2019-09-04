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
struct MPContext {int num_next_frames; int display_sync_broken; scalar_t__ vo_chain; int /*<<< orphan*/  video_status; scalar_t__ display_sync_drift_dir; scalar_t__ drop_message_shown; scalar_t__ mistimed_frames_total; scalar_t__ last_av_difference; scalar_t__ total_avsync_change; scalar_t__ num_past_frames; scalar_t__ last_frame_duration; int /*<<< orphan*/  video_pts; scalar_t__ time_frame; scalar_t__ delay; int /*<<< orphan*/  saved_frame; int /*<<< orphan*/ * next_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  STATUS_EOF ; 
 int /*<<< orphan*/  STATUS_SYNCING ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vo_chain_reset_state (scalar_t__) ; 

void reset_video_state(struct MPContext *mpctx)
{
    if (mpctx->vo_chain)
        vo_chain_reset_state(mpctx->vo_chain);

    for (int n = 0; n < mpctx->num_next_frames; n++)
        mp_image_unrefp(&mpctx->next_frames[n]);
    mpctx->num_next_frames = 0;
    mp_image_unrefp(&mpctx->saved_frame);

    mpctx->delay = 0;
    mpctx->time_frame = 0;
    mpctx->video_pts = MP_NOPTS_VALUE;
    mpctx->last_frame_duration = 0;
    mpctx->num_past_frames = 0;
    mpctx->total_avsync_change = 0;
    mpctx->last_av_difference = 0;
    mpctx->mistimed_frames_total = 0;
    mpctx->drop_message_shown = 0;
    mpctx->display_sync_drift_dir = 0;
    mpctx->display_sync_broken = false;

    mpctx->video_status = mpctx->vo_chain ? STATUS_SYNCING : STATUS_EOF;
}