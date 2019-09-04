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
struct demux_ctrl_reader_state {int idle; int ts_duration; int underrun; scalar_t__ eof; } ;
struct MPOpts {int cache_pause_wait; scalar_t__ cache_pause_initial; scalar_t__ cache_pause; } ;
struct MPContext {scalar_t__ video_status; scalar_t__ audio_status; int paused_for_cache; double cache_stop_time; double next_cache_update; int cache_buffer; scalar_t__ restart_complete; int /*<<< orphan*/  demuxer; struct MPOpts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUXER_CTRL_GET_READER_STATE ; 
 int MPCLAMP (int,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  MP_EVENT_CACHE_UPDATE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,int,int,...) ; 
 scalar_t__ STATUS_READY ; 
 int /*<<< orphan*/  demux_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct demux_ctrl_reader_state*) ; 
 scalar_t__ demux_is_network_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 double mp_time_sec () ; 
 int /*<<< orphan*/  prefetch_next (struct MPContext*) ; 
 int /*<<< orphan*/  update_internal_pause_state (struct MPContext*) ; 

__attribute__((used)) static void handle_pause_on_low_cache(struct MPContext *mpctx)
{
    bool force_update = false;
    struct MPOpts *opts = mpctx->opts;
    if (!mpctx->demuxer)
        return;

    double now = mp_time_sec();

    struct demux_ctrl_reader_state s = {.idle = true, .ts_duration = -1};
    demux_control(mpctx->demuxer, DEMUXER_CTRL_GET_READER_STATE, &s);

    int cache_buffer = 100;
    bool use_pause_on_low_cache = demux_is_network_cached(mpctx->demuxer) &&
                                  opts->cache_pause;

    if (!mpctx->restart_complete) {
        // Audio or video is restarting, and initial buffering is enabled. Make
        // sure we actually restart them in paused mode, so no audio gets
        // dropped and video technically doesn't start yet.
        use_pause_on_low_cache &= opts->cache_pause_initial &&
                                    (mpctx->video_status == STATUS_READY ||
                                     mpctx->audio_status == STATUS_READY);
    }

    bool is_low = use_pause_on_low_cache && !s.idle &&
                  s.ts_duration < opts->cache_pause_wait;

    // Enter buffering state only if there actually was an underrun (or if
    // initial caching before playback restart is used).
    if (is_low && !mpctx->paused_for_cache && mpctx->restart_complete)
        is_low = s.underrun;

    if (mpctx->paused_for_cache != is_low) {
        mpctx->paused_for_cache = is_low;
        update_internal_pause_state(mpctx);
        force_update = true;
        if (is_low)
            mpctx->cache_stop_time = now;
    }

    if (mpctx->paused_for_cache) {
        cache_buffer =
            100 * MPCLAMP(s.ts_duration / opts->cache_pause_wait, 0, 0.99);
        mp_set_timeout(mpctx, 0.2);
    }

    // Also update cache properties.
    bool busy = !s.idle;
    if (busy || mpctx->next_cache_update > 0) {
        if (mpctx->next_cache_update <= now) {
            mpctx->next_cache_update = busy ? now + 0.25 : 0;
            force_update = true;
        }
        if (mpctx->next_cache_update > 0)
            mp_set_timeout(mpctx, mpctx->next_cache_update - now);
    }

    if (mpctx->cache_buffer != cache_buffer) {
        if ((mpctx->cache_buffer == 100) != (cache_buffer == 100)) {
            if (cache_buffer < 100) {
                MP_VERBOSE(mpctx, "Enter buffering (buffer went from %d%% -> %d%%) [%fs].\n",
                           mpctx->cache_buffer, cache_buffer, s.ts_duration);
            } else {
                double t = now - mpctx->cache_stop_time;
                MP_VERBOSE(mpctx, "End buffering (waited %f secs) [%fs].\n",
                           t, s.ts_duration);
            }
        } else {
            MP_VERBOSE(mpctx, "Still buffering (buffer went from %d%% -> %d%%) [%fs].\n",
                       mpctx->cache_buffer, cache_buffer, s.ts_duration);
        }
        mpctx->cache_buffer = cache_buffer;
        force_update = true;
    }

    if (s.eof && !busy)
        prefetch_next(mpctx);

    if (force_update)
        mp_notify(mpctx, MP_EVENT_CACHE_UPDATE, NULL);
}