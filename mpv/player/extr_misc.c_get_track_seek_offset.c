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
struct track {scalar_t__ type; scalar_t__ selected; } ;
struct MPOpts {double audio_delay; TYPE_1__* subs_rend; } ;
struct MPContext {struct MPOpts* opts; } ;
struct TYPE_2__ {double sub_delay; } ;

/* Variables and functions */
 scalar_t__ STREAM_AUDIO ; 
 scalar_t__ STREAM_SUB ; 

double get_track_seek_offset(struct MPContext *mpctx, struct track *track)
{
    struct MPOpts *opts = mpctx->opts;
    if (track->selected) {
        if (track->type == STREAM_AUDIO)
            return -opts->audio_delay;
        if (track->type == STREAM_SUB)
            return -opts->subs_rend->sub_delay;
    }
    return 0;
}