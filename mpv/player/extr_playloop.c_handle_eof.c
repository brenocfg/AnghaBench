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
struct MPContext {scalar_t__ audio_status; scalar_t__ video_status; scalar_t__ stop_play; scalar_t__ vo_chain; scalar_t__ ao_chain; scalar_t__ video_out; scalar_t__ paused; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 scalar_t__ STATUS_EOF ; 
 scalar_t__ vo_has_frame (scalar_t__) ; 

__attribute__((used)) static void handle_eof(struct MPContext *mpctx)
{
    /* Don't quit while paused and we're displaying the last video frame. On the
     * other hand, if we don't have a video frame, then the user probably seeked
     * outside of the video, and we do want to quit. */
    bool prevent_eof =
        mpctx->paused && mpctx->video_out && vo_has_frame(mpctx->video_out);
    /* It's possible for the user to simultaneously switch both audio
     * and video streams to "disabled" at runtime. Handle this by waiting
     * rather than immediately stopping playback due to EOF.
     */
    if ((mpctx->ao_chain || mpctx->vo_chain) && !prevent_eof &&
        mpctx->audio_status == STATUS_EOF &&
        mpctx->video_status == STATUS_EOF &&
        !mpctx->stop_play)
    {
        mpctx->stop_play = AT_END_OF_FILE;
    }
}