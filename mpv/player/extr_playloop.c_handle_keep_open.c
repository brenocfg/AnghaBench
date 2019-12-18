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
struct MPOpts {int keep_open; int loop_times; scalar_t__ keep_open_pause; } ;
struct MPContext {scalar_t__ stop_play; scalar_t__ ao; int /*<<< orphan*/  last_vo_pts; int /*<<< orphan*/  playback_pts; int /*<<< orphan*/  video_out; scalar_t__ vo_chain; int /*<<< orphan*/  playlist; struct MPOpts* opts; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 scalar_t__ KEEP_PLAYING ; 
 int /*<<< orphan*/  ao_drain (scalar_t__) ; 
 int /*<<< orphan*/  playlist_get_next (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seek_to_last_frame (struct MPContext*) ; 
 int /*<<< orphan*/  set_pause_state (struct MPContext*,int) ; 
 int /*<<< orphan*/  vo_has_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_keep_open(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    if (opts->keep_open && mpctx->stop_play == AT_END_OF_FILE &&
        (opts->keep_open == 2 || !playlist_get_next(mpctx->playlist, 1)) &&
        opts->loop_times == 1)
    {
        mpctx->stop_play = KEEP_PLAYING;
        if (mpctx->vo_chain) {
            if (!vo_has_frame(mpctx->video_out)) // EOF not reached normally
                seek_to_last_frame(mpctx);
            mpctx->playback_pts = mpctx->last_vo_pts;
        }
        if (opts->keep_open_pause) {
            if (mpctx->ao)
                ao_drain(mpctx->ao);
            set_pause_state(mpctx, true);
        }
    }
}