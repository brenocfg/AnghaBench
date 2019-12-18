#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mp_chmap {int dummy; } ;
struct ao_chain {scalar_t__ ao_resume_time; int underrun; int /*<<< orphan*/  ao_buffer; TYPE_1__* filter; TYPE_4__* track; } ;
struct MPOpts {int sync_max_audio_change; int sync_max_video_change; scalar_t__ video_sync; double sync_audio_drop_size; scalar_t__ gapless_audio; } ;
struct MPContext {scalar_t__ audio_status; int audio_speed; scalar_t__ video_status; scalar_t__ delay; scalar_t__ last_av_difference; double audio_drop_throttle; int /*<<< orphan*/  encode_lavc_ctx; scalar_t__ ao; scalar_t__ paused; scalar_t__ display_sync_active; scalar_t__ vo_chain; struct ao_chain* ao_chain; struct MPOpts* opts; } ;
struct TYPE_8__ {TYPE_2__* dec; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pins; } ;
struct TYPE_6__ {scalar_t__ pts_reset; } ;
struct TYPE_5__ {scalar_t__ ao_needs_update; TYPE_3__* f; scalar_t__ got_output_eof; scalar_t__ failed_output_conversion; } ;

/* Variables and functions */
 int AD_EOF ; 
 int AD_OK ; 
 int AD_WAIT ; 
 int AOPLAY_FINAL_CHUNK ; 
 int /*<<< orphan*/  AO_EVENT_INITIAL_UNBLOCK ; 
 int /*<<< orphan*/  AO_EVENT_RELOAD ; 
 int /*<<< orphan*/  AO_EVENT_UNDERRUN ; 
 int MPMAX (int,int) ; 
 int MPMIN (int,int) ; 
 int /*<<< orphan*/  MP_STATS (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*) ; 
 scalar_t__ STATUS_DRAINING ; 
 scalar_t__ STATUS_EOF ; 
 scalar_t__ STATUS_FILLING ; 
 scalar_t__ STATUS_PLAYING ; 
 scalar_t__ STATUS_READY ; 
 scalar_t__ STATUS_SYNCING ; 
 int /*<<< orphan*/  STREAM_AUDIO ; 
 scalar_t__ VS_DISP_ADROP ; 
 int abs (int) ; 
 int af_format_sample_alignment (int) ; 
 scalar_t__ ao_eof_reached (scalar_t__) ; 
 int /*<<< orphan*/  ao_get_format (scalar_t__,int*,int*,struct mp_chmap*) ; 
 int ao_get_space (scalar_t__) ; 
 scalar_t__ ao_query_and_reset_events (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_reset (scalar_t__) ; 
 int /*<<< orphan*/  ao_unblock (scalar_t__) ; 
 scalar_t__ ao_untimed (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ceil (double) ; 
 int /*<<< orphan*/  dump_audio_stats (struct MPContext*) ; 
 int /*<<< orphan*/  encode_lavc_stream_eof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_on_track (struct MPContext*,TYPE_4__*) ; 
 double fabs (scalar_t__) ; 
 int filter_audio (struct MPContext*,int /*<<< orphan*/ ,int) ; 
 int get_sync_samples (struct MPContext*,int*) ; 
 int /*<<< orphan*/  mp_audio_buffer_duplicate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_audio_buffer_peek (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  mp_audio_buffer_prepend_silence (int /*<<< orphan*/ ,int) ; 
 int mp_audio_buffer_samples (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_audio_buffer_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_filter_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  mp_pin_out_request_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 scalar_t__ mp_time_sec () ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  reinit_audio_filters_and_output (struct MPContext*) ; 
 int /*<<< orphan*/  reload_audio_output (struct MPContext*) ; 
 int /*<<< orphan*/  reset_playback_state (struct MPContext*) ; 
 int write_to_ao (struct MPContext*,int /*<<< orphan*/ **,int,int) ; 

void fill_audio_out_buffers(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    bool was_eof = mpctx->audio_status == STATUS_EOF;

    dump_audio_stats(mpctx);

    if (mpctx->ao && ao_query_and_reset_events(mpctx->ao, AO_EVENT_RELOAD))
        reload_audio_output(mpctx);

    if (mpctx->ao && ao_query_and_reset_events(mpctx->ao,
                                               AO_EVENT_INITIAL_UNBLOCK))
        ao_unblock(mpctx->ao);

    struct ao_chain *ao_c = mpctx->ao_chain;
    if (!ao_c)
        return;

    if (ao_c->filter->failed_output_conversion) {
        error_on_track(mpctx, ao_c->track);
        return;
    }

    // (if AO is set due to gapless from previous file, then we can try to
    // filter normally until the filter tells us to change the AO)
    if (!mpctx->ao) {
        // Probe the initial audio format.
        mp_pin_out_request_data(ao_c->filter->f->pins[1]);
        reinit_audio_filters_and_output(mpctx);
        if (!mpctx->ao_chain)
            return;
        if (ao_c->filter->got_output_eof &&
            mpctx->audio_status != STATUS_EOF)
        {
            mpctx->audio_status = STATUS_EOF;
            MP_VERBOSE(mpctx, "audio EOF without any data\n");
            mp_filter_reset(ao_c->filter->f);
            encode_lavc_stream_eof(mpctx->encode_lavc_ctx, STREAM_AUDIO);
        }
        return; // try again next iteration
    }

    if (ao_c->ao_resume_time > mp_time_sec()) {
        double remaining = ao_c->ao_resume_time - mp_time_sec();
        mp_set_timeout(mpctx, remaining);
        return;
    }

    if (mpctx->vo_chain && ao_c->track && ao_c->track->dec &&
        ao_c->track->dec->pts_reset)
    {
        MP_WARN(mpctx, "Reset playback due to audio timestamp reset.\n");
        reset_playback_state(mpctx);
        mp_wakeup_core(mpctx);
        return;
    }

    int ao_rate;
    int ao_format;
    struct mp_chmap ao_channels;
    ao_get_format(mpctx->ao, &ao_rate, &ao_format, &ao_channels);
    double play_samplerate = ao_rate / mpctx->audio_speed;
    int align = af_format_sample_alignment(ao_format);

    // If audio is infinitely fast, somehow try keeping approximate A/V sync.
    if (mpctx->audio_status == STATUS_PLAYING && ao_untimed(mpctx->ao) &&
        mpctx->video_status != STATUS_EOF && mpctx->delay > 0)
        return;

    int playsize = ao_get_space(mpctx->ao);

    if (ao_query_and_reset_events(mpctx->ao, AO_EVENT_UNDERRUN))
        ao_c->underrun = true;

    // Stop feeding data if an underrun happened. Something else needs to
    // "unblock" audio after underrun. handle_update_cache() does this and can
    // take the network state into account.
    if (ao_c->underrun)
        return;

    int skip = 0;
    bool sync_known = get_sync_samples(mpctx, &skip);
    if (skip > 0) {
        playsize = MPMIN(skip + 1, MPMAX(playsize, 2500)); // buffer extra data
    } else if (skip < 0) {
        playsize = MPMAX(1, playsize + skip); // silence will be prepended
    }

    int skip_duplicate = 0; // >0: skip, <0: duplicate
    double drop_limit =
        (opts->sync_max_audio_change + opts->sync_max_video_change) / 100;
    if (mpctx->display_sync_active && opts->video_sync == VS_DISP_ADROP &&
        fabs(mpctx->last_av_difference) >= opts->sync_audio_drop_size &&
        mpctx->audio_drop_throttle < drop_limit &&
        mpctx->audio_status == STATUS_PLAYING)
    {
        int samples = ceil(opts->sync_audio_drop_size * play_samplerate);
        samples = (samples + align / 2) / align * align;

        skip_duplicate = mpctx->last_av_difference >= 0 ? -samples : samples;

        playsize = MPMAX(playsize, samples);

        mpctx->audio_drop_throttle += 1 - drop_limit - samples / play_samplerate;
    }

    playsize = playsize / align * align;

    int status = mpctx->audio_status >= STATUS_DRAINING ? AD_EOF : AD_OK;
    bool working = false;
    if (playsize > mp_audio_buffer_samples(ao_c->ao_buffer)) {
        status = filter_audio(mpctx, ao_c->ao_buffer, playsize);
        if (ao_c->filter->ao_needs_update) {
            reinit_audio_filters_and_output(mpctx);
            mp_wakeup_core(mpctx);
            return; // retry on next iteration
        }
        if (status == AD_WAIT)
            return;
        working = true;
    }

    // If EOF was reached before, but now something can be decoded, try to
    // restart audio properly. This helps with video files where audio starts
    // later. Retrying is needed to get the correct sync PTS.
    if (mpctx->audio_status >= STATUS_DRAINING &&
        mp_audio_buffer_samples(ao_c->ao_buffer) > 0)
    {
        mpctx->audio_status = STATUS_SYNCING;
        return; // retry on next iteration
    }

    bool end_sync = false;
    if (skip >= 0) {
        int max = mp_audio_buffer_samples(ao_c->ao_buffer);
        mp_audio_buffer_skip(ao_c->ao_buffer, MPMIN(skip, max));
        // If something is left, we definitely reached the target time.
        end_sync |= sync_known && skip < max;
        working |= skip > 0;
    } else if (skip < 0) {
        if (-skip > playsize) { // heuristic against making the buffer too large
            ao_reset(mpctx->ao); // some AOs repeat data on underflow
            mpctx->audio_status = STATUS_DRAINING;
            mpctx->delay = 0;
            return;
        }
        mp_audio_buffer_prepend_silence(ao_c->ao_buffer, -skip);
        end_sync = true;
    }

    if (skip_duplicate) {
        int max = mp_audio_buffer_samples(ao_c->ao_buffer);
        if (abs(skip_duplicate) > max)
            skip_duplicate = skip_duplicate >= 0 ? max : -max;
        mpctx->last_av_difference += skip_duplicate / play_samplerate;
        if (skip_duplicate >= 0) {
            mp_audio_buffer_skip(ao_c->ao_buffer, skip_duplicate);
            MP_STATS(mpctx, "drop-audio");
        } else {
            mp_audio_buffer_duplicate(ao_c->ao_buffer, -skip_duplicate);
            MP_STATS(mpctx, "duplicate-audio");
        }
        MP_VERBOSE(mpctx, "audio skip_duplicate=%d\n", skip_duplicate);
    }

    if (mpctx->audio_status == STATUS_SYNCING) {
        if (end_sync)
            mpctx->audio_status = STATUS_FILLING;
        if (status != AD_OK && !mp_audio_buffer_samples(ao_c->ao_buffer))
            mpctx->audio_status = STATUS_EOF;
        if (working || end_sync)
            mp_wakeup_core(mpctx);
        return; // continue on next iteration
    }

    assert(mpctx->audio_status >= STATUS_FILLING);

    // We already have as much data as the audio device wants, and can start
    // writing it any time.
    if (mpctx->audio_status == STATUS_FILLING)
        mpctx->audio_status = STATUS_READY;

    // Even if we're done decoding and syncing, let video start first - this is
    // required, because sending audio to the AO already starts playback.
    if (mpctx->audio_status == STATUS_READY) {
        // Warning: relies on handle_playback_restart() being called afterwards.
        return;
    }

    bool audio_eof = status == AD_EOF;
    bool partial_fill = false;
    int playflags = 0;

    if (playsize > mp_audio_buffer_samples(ao_c->ao_buffer)) {
        playsize = mp_audio_buffer_samples(ao_c->ao_buffer);
        partial_fill = true;
    }

    audio_eof &= partial_fill;

    if (audio_eof && playsize < align)
        playsize = 0;

    // With gapless audio, delay this to ao_uninit. There must be only
    // 1 final chunk, and that is handled when calling ao_uninit().
    // If video is still on-going, trying to do gapless is pointless, as video
    // will have to continue for a while with audio stopped (but still try to
    // do it if gapless is forced, mostly for testing).
    if (audio_eof && (!opts->gapless_audio ||
        (opts->gapless_audio <= 0 && mpctx->video_status != STATUS_EOF)))
        playflags |= AOPLAY_FINAL_CHUNK;

    uint8_t **planes;
    int samples;
    mp_audio_buffer_peek(ao_c->ao_buffer, &planes, &samples);
    if (audio_eof || samples >= align)
        samples = samples / align * align;
    samples = MPMIN(samples, mpctx->paused ? 0 : playsize);
    int played = write_to_ao(mpctx, planes, samples, playflags);
    assert(played >= 0 && played <= samples);
    mp_audio_buffer_skip(ao_c->ao_buffer, played);

    mpctx->audio_drop_throttle =
        MPMAX(0, mpctx->audio_drop_throttle - played / play_samplerate);

    dump_audio_stats(mpctx);

    mpctx->audio_status = STATUS_PLAYING;
    if (audio_eof && !playsize) {
        mpctx->audio_status = STATUS_DRAINING;
        // Wait until the AO has played all queued data. In the gapless case,
        // we trigger EOF immediately, and let it play asynchronously.
        if (ao_eof_reached(mpctx->ao) || opts->gapless_audio) {
            mpctx->audio_status = STATUS_EOF;
            if (!was_eof) {
                MP_VERBOSE(mpctx, "audio EOF reached\n");
                mp_wakeup_core(mpctx);
                encode_lavc_stream_eof(mpctx->encode_lavc_ctx, STREAM_AUDIO);
            }
        }
    }
}