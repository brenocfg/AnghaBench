#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  stream; } ;
struct pa_sample_spec {int dummy; } ;
struct ao {struct priv* priv; } ;
struct TYPE_3__ {scalar_t__ sink_usec; scalar_t__ since_underrun; int /*<<< orphan*/  playing; scalar_t__ transport_usec; scalar_t__ read_index; scalar_t__ write_index; } ;
typedef  TYPE_1__ pa_timing_info ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC_ERR_MSG (char*) ; 
 scalar_t__ pa_bytes_to_usec (scalar_t__,struct pa_sample_spec const*) ; 
 struct pa_sample_spec* pa_stream_get_sample_spec (int /*<<< orphan*/ ) ; 
 TYPE_1__* pa_stream_get_timing_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_stream_update_timing_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitop (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double get_delay_hackfixed(struct ao *ao)
{
    /* This code basically does what pa_stream_get_latency() _should_
     * do, but doesn't due to multiple known bugs in PulseAudio (at
     * PulseAudio version 2.1). In particular, the timing interpolation
     * mode (PA_STREAM_INTERPOLATE_TIMING) can return completely bogus
     * values, and the non-interpolating code has a bug causing too
     * large results at end of stream (so a stream never seems to finish).
     * This code can still return wrong values in some cases due to known
     * PulseAudio bugs that can not be worked around on the client side.
     *
     * We always query the server for latest timing info. This may take
     * too long to work well with remote audio servers, but at least
     * this should be enough to fix the normal local playback case.
     */
    struct priv *priv = ao->priv;
    pa_threaded_mainloop_lock(priv->mainloop);
    if (!waitop(priv, pa_stream_update_timing_info(priv->stream, NULL, NULL))) {
        GENERIC_ERR_MSG("pa_stream_update_timing_info() failed");
        return 0;
    }
    pa_threaded_mainloop_lock(priv->mainloop);
    const pa_timing_info *ti = pa_stream_get_timing_info(priv->stream);
    if (!ti) {
        pa_threaded_mainloop_unlock(priv->mainloop);
        GENERIC_ERR_MSG("pa_stream_get_timing_info() failed");
        return 0;
    }
    const struct pa_sample_spec *ss = pa_stream_get_sample_spec(priv->stream);
    if (!ss) {
        pa_threaded_mainloop_unlock(priv->mainloop);
        GENERIC_ERR_MSG("pa_stream_get_sample_spec() failed");
        return 0;
    }
    // data left in PulseAudio's main buffers (not written to sink yet)
    int64_t latency = pa_bytes_to_usec(ti->write_index - ti->read_index, ss);
    // since this info may be from a while ago, playback has progressed since
    latency -= ti->transport_usec;
    // data already moved from buffers to sink, but not played yet
    int64_t sink_latency = ti->sink_usec;
    if (!ti->playing)
        /* At the end of a stream, part of the data "left" in the sink may
         * be padding silence after the end; that should be subtracted to
         * get the amount of real audio from our stream. This adjustment
         * is missing from Pulseaudio's own get_latency calculations
         * (as of PulseAudio 2.1). */
        sink_latency -= pa_bytes_to_usec(ti->since_underrun, ss);
    if (sink_latency > 0)
        latency += sink_latency;
    if (latency < 0)
        latency = 0;
    pa_threaded_mainloop_unlock(priv->mainloop);
    return latency / 1e6;
}