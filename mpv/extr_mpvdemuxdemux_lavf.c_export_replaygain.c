#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {TYPE_1__* codec; int /*<<< orphan*/  ds; } ;
struct replaygain_data {float track_gain; float track_peak; float album_gain; float album_peak; } ;
typedef  int /*<<< orphan*/  demuxer_t ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ data; } ;
struct TYPE_8__ {float track_gain; double track_peak; float album_gain; double album_peak; } ;
struct TYPE_7__ {int nb_side_data; TYPE_4__* side_data; } ;
struct TYPE_6__ {struct replaygain_data* replaygain_data; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVReplayGain ;
typedef  TYPE_4__ AVPacketSideData ;

/* Variables and functions */
 scalar_t__ AV_PKT_DATA_REPLAYGAIN ; 
 float INT32_MIN ; 
 int /*<<< orphan*/  assert (int) ; 
 struct replaygain_data* talloc_ptrtype (int /*<<< orphan*/ *,struct replaygain_data*) ; 

__attribute__((used)) static void export_replaygain(demuxer_t *demuxer, struct sh_stream *sh,
                              AVStream *st)
{
    for (int i = 0; i < st->nb_side_data; i++) {
        AVReplayGain *av_rgain;
        struct replaygain_data *rgain;
        AVPacketSideData *src_sd = &st->side_data[i];

        if (src_sd->type != AV_PKT_DATA_REPLAYGAIN)
            continue;

        av_rgain = (AVReplayGain*)src_sd->data;
        rgain    = talloc_ptrtype(demuxer, rgain);

        // Set values in *rgain, using track gain as a fallback for album gain
        // if the latter is not present. This behavior matches that in
        // demux/demux.c's decode_rgain; if you change this, please make
        // equivalent changes there too.
        if (av_rgain->track_gain != INT32_MIN && av_rgain->track_peak != 0.0) {
            // Track gain is defined.
            rgain->track_gain = av_rgain->track_gain / 100000.0f;
            rgain->track_peak = av_rgain->track_peak / 100000.0f;

            if (av_rgain->album_gain != INT32_MIN &&
                av_rgain->album_peak != 0.0)
            {
                // Album gain is also defined.
                rgain->album_gain = av_rgain->album_gain / 100000.0f;
                rgain->album_peak = av_rgain->album_peak / 100000.0f;
            } else {
                // Album gain is undefined; fall back to track gain.
                rgain->album_gain = rgain->track_gain;
                rgain->album_peak = rgain->track_peak;
            }
        }

        // This must be run only before the stream was added, otherwise there
        // will be race conditions with accesses from the user thread.
        assert(!sh->ds);
        sh->codec->replaygain_data = rgain;
    }
}