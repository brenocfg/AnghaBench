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
struct MPContext {scalar_t__ video_status; scalar_t__ audio_status; int /*<<< orphan*/  playback_pts; int /*<<< orphan*/  video_pts; TYPE_1__* vo_chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_sparse; int /*<<< orphan*/  is_coverart; } ;

/* Variables and functions */
 scalar_t__ STATUS_EOF ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  playing_audio_pts (struct MPContext*) ; 

__attribute__((used)) static void handle_playback_time(struct MPContext *mpctx)
{
    if (mpctx->vo_chain &&
        !mpctx->vo_chain->is_coverart &&
        !mpctx->vo_chain->is_sparse &&
        mpctx->video_status >= STATUS_PLAYING &&
        mpctx->video_status < STATUS_EOF)
    {
        mpctx->playback_pts = mpctx->video_pts;
    } else if (mpctx->audio_status >= STATUS_PLAYING &&
               mpctx->audio_status < STATUS_EOF)
    {
        mpctx->playback_pts = playing_audio_pts(mpctx);
    }
}