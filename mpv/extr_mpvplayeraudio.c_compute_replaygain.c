#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct track {TYPE_2__* stream; } ;
struct replaygain_data {float track_gain; float track_peak; float album_gain; float album_peak; } ;
struct MPOpts {int rgain_mode; float rgain_fallback; int /*<<< orphan*/  rgain_clip; scalar_t__ rgain_preamp; } ;
struct MPContext {struct track*** current_track; struct MPOpts* opts; } ;
struct TYPE_4__ {TYPE_1__* codec; } ;
struct TYPE_3__ {struct replaygain_data* replaygain_data; } ;

/* Variables and functions */
 float MPMIN (float,double) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,float,...) ; 
 size_t STREAM_AUDIO ; 
 float db_gain (float) ; 

__attribute__((used)) static float compute_replaygain(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;

    float rgain = 1.0;

    struct replaygain_data *rg = NULL;
    struct track *track = mpctx->current_track[0][STREAM_AUDIO];
    if (track)
        rg = track->stream->codec->replaygain_data;
    if (opts->rgain_mode && rg) {
        MP_VERBOSE(mpctx, "Replaygain: Track=%f/%f Album=%f/%f\n",
                   rg->track_gain, rg->track_peak,
                   rg->album_gain, rg->album_peak);

        float gain, peak;
        if (opts->rgain_mode == 1) {
            gain = rg->track_gain;
            peak = rg->track_peak;
        } else {
            gain = rg->album_gain;
            peak = rg->album_peak;
        }

        gain += opts->rgain_preamp;
        rgain = db_gain(gain);

        MP_VERBOSE(mpctx, "Applying replay-gain: %f\n", rgain);

        if (!opts->rgain_clip) { // clipping prevention
            rgain = MPMIN(rgain, 1.0 / peak);
            MP_VERBOSE(mpctx, "...with clipping prevention: %f\n", rgain);
        }
    } else if (opts->rgain_fallback) {
        rgain = db_gain(opts->rgain_fallback);
        MP_VERBOSE(mpctx, "Applying fallback gain: %f\n", rgain);
    }

    return rgain;
}