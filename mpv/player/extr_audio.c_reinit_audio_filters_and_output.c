#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct track {TYPE_4__* dec; } ;
struct mp_chmap {int /*<<< orphan*/  member_0; } ;
struct mp_aframe {int dummy; } ;
struct ao_chain {int spdif_passthrough; int spdif_failed; scalar_t__ ao_resume_time; TYPE_2__* filter; int /*<<< orphan*/  ao_buffer; struct track* track; int /*<<< orphan*/ * ao; int /*<<< orphan*/  output_frame; } ;
struct TYPE_5__ {int num_chmaps; int /*<<< orphan*/ * chmaps; scalar_t__ auto_safe; int /*<<< orphan*/  set; } ;
struct MPOpts {scalar_t__ gapless_audio; scalar_t__ audio_wait_open; TYPE_1__ audio_output_channels; scalar_t__ audio_exclusive; scalar_t__ audio_stream_silence; scalar_t__ ao_null_fallback; scalar_t__ audio_output_format; scalar_t__ force_srate; } ;
struct MPContext {int /*<<< orphan*/ * ao; int /*<<< orphan*/  error_playing; int /*<<< orphan*/  encode_lavc_ctx; int /*<<< orphan*/  global; struct mp_aframe* ao_filter_fmt; struct ao_chain* ao_chain; struct MPOpts* opts; } ;
struct TYPE_7__ {int try_spdif; } ;
struct TYPE_6__ {int /*<<< orphan*/  output_aformat; int /*<<< orphan*/  ao_needs_update; } ;

/* Variables and functions */
 int AO_INIT_EXCLUSIVE ; 
 int AO_INIT_NULL_FALLBACK ; 
 int AO_INIT_SAFE_MULTICHANNEL_ONLY ; 
 int AO_INIT_STREAM_SILENCE ; 
 int /*<<< orphan*/  MPV_ERROR_AO_INIT_FAILED ; 
 int /*<<< orphan*/  MPV_EVENT_AUDIO_RECONFIG ; 
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MP_INFO (struct MPContext*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,...) ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ af_fmt_is_pcm (int) ; 
 scalar_t__ af_fmt_is_spdif (int) ; 
 int /*<<< orphan*/  ao_get_description (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ao_get_format (int /*<<< orphan*/ *,int*,int*,struct mp_chmap*) ; 
 int /*<<< orphan*/  ao_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ao_init_best (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct MPContext*,int /*<<< orphan*/ ,int,int,struct mp_chmap) ; 
 int /*<<< orphan*/  ao_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (struct ao_chain*) ; 
 int /*<<< orphan*/  audio_config_to_str_buf (char*,int,int,int,struct mp_chmap) ; 
 int /*<<< orphan*/  audio_update_volume (struct MPContext*) ; 
 int /*<<< orphan*/  error_on_track (struct MPContext*,struct track*) ; 
 scalar_t__ keep_weak_gapless_format (struct mp_aframe*,struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_config_is_valid (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_get_chmap (struct mp_aframe*,struct mp_chmap*) ; 
 int mp_aframe_get_format (struct mp_aframe*) ; 
 int mp_aframe_get_rate (struct mp_aframe*) ; 
 struct mp_aframe* mp_aframe_new_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_aframe_set_chmap (struct mp_aframe*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_aframe_set_format (struct mp_aframe*,scalar_t__) ; 
 int /*<<< orphan*/  mp_aframe_set_rate (struct mp_aframe*,scalar_t__) ; 
 int /*<<< orphan*/  mp_audio_buffer_reinit_fmt (int /*<<< orphan*/ ,int,struct mp_chmap*,int) ; 
 int /*<<< orphan*/  mp_chmap_equals (struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_sel_list (struct mp_chmap*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_decoder_wrapper_reinit (TYPE_4__*) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_output_chain_reset_harder (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_output_chain_set_ao (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_time_sec () ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wakeup_core_cb ; 
 int /*<<< orphan*/  reset_audio_state (struct MPContext*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_aframe*) ; 
 int /*<<< orphan*/  uninit_audio_chain (struct MPContext*) ; 
 int /*<<< orphan*/  uninit_audio_out (struct MPContext*) ; 
 int /*<<< orphan*/  update_window_title (struct MPContext*,int) ; 

__attribute__((used)) static void reinit_audio_filters_and_output(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    struct ao_chain *ao_c = mpctx->ao_chain;
    assert(ao_c);
    struct track *track = ao_c->track;

    if (!ao_c->filter->ao_needs_update)
        return;

    TA_FREEP(&ao_c->output_frame); // stale?

    // The "ideal" filter output format
    struct mp_aframe *out_fmt = mp_aframe_new_ref(ao_c->filter->output_aformat);
    if (!out_fmt)
        abort();

    if (!mp_aframe_config_is_valid(out_fmt)) {
        talloc_free(out_fmt);
        goto init_error;
    }

    if (af_fmt_is_pcm(mp_aframe_get_format(out_fmt))) {
        if (opts->force_srate)
            mp_aframe_set_rate(out_fmt, opts->force_srate);
        if (opts->audio_output_format)
            mp_aframe_set_format(out_fmt, opts->audio_output_format);
        if (opts->audio_output_channels.num_chmaps == 1)
            mp_aframe_set_chmap(out_fmt, &opts->audio_output_channels.chmaps[0]);
    }

    // Weak gapless audio: if the filter output format is the same as the
    // previous one, keep the AO and don't reinit anything.
    // Strong gapless: always keep the AO
    if ((mpctx->ao_filter_fmt && mpctx->ao && opts->gapless_audio < 0 &&
         keep_weak_gapless_format(mpctx->ao_filter_fmt, out_fmt)) ||
        (mpctx->ao && opts->gapless_audio > 0))
    {
        mp_output_chain_set_ao(ao_c->filter, mpctx->ao);
        talloc_free(out_fmt);
        return;
    }

    uninit_audio_out(mpctx);

    int out_rate = mp_aframe_get_rate(out_fmt);
    int out_format = mp_aframe_get_format(out_fmt);
    struct mp_chmap out_channels = {0};
    mp_aframe_get_chmap(out_fmt, &out_channels);

    int ao_flags = 0;
    bool spdif_fallback = af_fmt_is_spdif(out_format) &&
                          ao_c->spdif_passthrough;

    if (opts->ao_null_fallback && !spdif_fallback)
        ao_flags |= AO_INIT_NULL_FALLBACK;

    if (opts->audio_stream_silence)
        ao_flags |= AO_INIT_STREAM_SILENCE;

    if (opts->audio_exclusive)
        ao_flags |= AO_INIT_EXCLUSIVE;

    if (af_fmt_is_pcm(out_format)) {
        if (!opts->audio_output_channels.set ||
            opts->audio_output_channels.auto_safe)
            ao_flags |= AO_INIT_SAFE_MULTICHANNEL_ONLY;

        mp_chmap_sel_list(&out_channels,
                          opts->audio_output_channels.chmaps,
                          opts->audio_output_channels.num_chmaps);
    }

    mpctx->ao_filter_fmt = out_fmt;

    mpctx->ao = ao_init_best(mpctx->global, ao_flags, mp_wakeup_core_cb,
                             mpctx, mpctx->encode_lavc_ctx, out_rate,
                             out_format, out_channels);
    ao_c->ao = mpctx->ao;

    int ao_rate = 0;
    int ao_format = 0;
    struct mp_chmap ao_channels = {0};
    if (mpctx->ao)
        ao_get_format(mpctx->ao, &ao_rate, &ao_format, &ao_channels);

    // Verify passthrough format was not changed.
    if (mpctx->ao && af_fmt_is_spdif(out_format)) {
        if (out_rate != ao_rate || out_format != ao_format ||
            !mp_chmap_equals(&out_channels, &ao_channels))
        {
            MP_ERR(mpctx, "Passthrough format unsupported.\n");
            ao_uninit(mpctx->ao);
            mpctx->ao = NULL;
            ao_c->ao = NULL;
        }
    }

    if (!mpctx->ao) {
        // If spdif was used, try to fallback to PCM.
        if (spdif_fallback && ao_c->track && ao_c->track->dec) {
            MP_VERBOSE(mpctx, "Falling back to PCM output.\n");
            ao_c->spdif_passthrough = false;
            ao_c->spdif_failed = true;
            ao_c->track->dec->try_spdif = false;
            if (!mp_decoder_wrapper_reinit(ao_c->track->dec))
                goto init_error;
            reset_audio_state(mpctx);
            mp_output_chain_reset_harder(ao_c->filter);
            mp_wakeup_core(mpctx); // reinit with new format next time
            return;
        }

        MP_ERR(mpctx, "Could not open/initialize audio device -> no sound.\n");
        mpctx->error_playing = MPV_ERROR_AO_INIT_FAILED;
        goto init_error;
    }

    mp_audio_buffer_reinit_fmt(ao_c->ao_buffer, ao_format, &ao_channels,
                                ao_rate);

    char tmp[192];
    MP_INFO(mpctx, "AO: [%s] %s\n", ao_get_name(mpctx->ao),
            audio_config_to_str_buf(tmp, sizeof(tmp), ao_rate, ao_format,
                                    ao_channels));
    MP_VERBOSE(mpctx, "AO: Description: %s\n", ao_get_description(mpctx->ao));
    update_window_title(mpctx, true);

    ao_c->ao_resume_time =
        opts->audio_wait_open > 0 ? mp_time_sec() + opts->audio_wait_open : 0;

    mp_output_chain_set_ao(ao_c->filter, mpctx->ao);

    audio_update_volume(mpctx);

    mp_notify(mpctx, MPV_EVENT_AUDIO_RECONFIG, NULL);

    return;

init_error:
    uninit_audio_chain(mpctx);
    uninit_audio_out(mpctx);
    error_on_track(mpctx, track);
}