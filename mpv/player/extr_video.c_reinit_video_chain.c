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
 size_t STREAM_VIDEO ; 
 int /*<<< orphan*/  error_on_track (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  reinit_video_chain_src (struct MPContext*,struct track*) ; 

void reinit_video_chain(struct MPContext *mpctx)
{
    struct track *track = mpctx->current_track[0][STREAM_VIDEO];
    if (!track || !track->stream) {
        error_on_track(mpctx, track);
        return;
    }
    reinit_video_chain_src(mpctx, track);
}