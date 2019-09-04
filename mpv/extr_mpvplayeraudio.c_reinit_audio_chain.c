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
struct track {int /*<<< orphan*/  stream; } ;
struct MPContext {struct track*** current_track; } ;

/* Variables and functions */
 size_t STREAM_AUDIO ; 
 int /*<<< orphan*/  error_on_track (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  reinit_audio_chain_src (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  uninit_audio_out (struct MPContext*) ; 

void reinit_audio_chain(struct MPContext *mpctx)
{
    struct track *track = NULL;
    track = mpctx->current_track[0][STREAM_AUDIO];
    if (!track || !track->stream) {
        uninit_audio_out(mpctx);
        error_on_track(mpctx, track);
        return;
    }
    reinit_audio_chain_src(mpctx, track);
}