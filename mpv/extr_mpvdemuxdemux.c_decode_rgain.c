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
struct replaygain_data {int /*<<< orphan*/  track_peak; int /*<<< orphan*/  album_peak; int /*<<< orphan*/  track_gain; int /*<<< orphan*/  album_gain; int /*<<< orphan*/  member_0; } ;
struct mp_tags {int dummy; } ;
struct mp_log {int dummy; } ;

/* Variables and functions */
 scalar_t__ decode_gain (struct mp_log*,struct mp_tags*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_peak (struct mp_log*,struct mp_tags*,char*,int /*<<< orphan*/ *) ; 
 struct replaygain_data* talloc_dup (int /*<<< orphan*/ *,struct replaygain_data*) ; 

__attribute__((used)) static struct replaygain_data *decode_rgain(struct mp_log *log,
                                            struct mp_tags *tags)
{
    struct replaygain_data rg = {0};

    // Set values in *rg, using track gain as a fallback for album gain if the
    // latter is not present. This behavior matches that in demux/demux_lavf.c's
    // export_replaygain; if you change this, please make equivalent changes
    // there too.
    if (decode_gain(log, tags, "REPLAYGAIN_TRACK_GAIN", &rg.track_gain) >= 0 &&
        decode_peak(log, tags, "REPLAYGAIN_TRACK_PEAK", &rg.track_peak) >= 0)
    {
        if (decode_gain(log, tags, "REPLAYGAIN_ALBUM_GAIN", &rg.album_gain) < 0 ||
            decode_peak(log, tags, "REPLAYGAIN_ALBUM_PEAK", &rg.album_peak) < 0)
        {
            // Album gain is undefined; fall back to track gain.
            rg.album_gain = rg.track_gain;
            rg.album_peak = rg.track_peak;
        }
        return talloc_dup(NULL, &rg);
    }

    if (decode_gain(log, tags, "REPLAYGAIN_GAIN", &rg.track_gain) >= 0 &&
        decode_peak(log, tags, "REPLAYGAIN_PEAK", &rg.track_peak) >= 0)
    {
        rg.album_gain = rg.track_gain;
        rg.album_peak = rg.track_peak;
        return talloc_dup(NULL, &rg);
    }

    return NULL;
}