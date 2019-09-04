#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  int /*<<< orphan*/  snd_pcm_sw_params_t ;
typedef  int /*<<< orphan*/  snd_pcm_hw_params_t ;
struct TYPE_5__ {int buffer_time; int period_time; int chunk_size; int bits_per_sample; int bits_per_frame; int /*<<< orphan*/  log; int /*<<< orphan*/  handle; } ;
struct TYPE_6__ {int req_channels; int channels; unsigned int req_samplerate; unsigned int samplerate; int blocksize; int samplesize; int bytes_per_sample; TYPE_1__ alsa; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  MSGL_V ; 
 int /*<<< orphan*/  SND_PCM_ACCESS_RW_INTERLEAVED ; 
 int /*<<< orphan*/  SND_PCM_FORMAT_S16 ; 
 scalar_t__ mp_msg_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_params_alloca (int /*<<< orphan*/ **) ; 
 int snd_pcm_hw_params_any (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_params_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_params_get_buffer_size (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  snd_pcm_hw_params_get_channels (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  snd_pcm_hw_params_get_period_size (int /*<<< orphan*/ *,scalar_t__*,int*) ; 
 int snd_pcm_hw_params_set_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params_set_buffer_time_near (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int snd_pcm_hw_params_set_channels (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_pcm_hw_params_set_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params_set_period_time_near (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int snd_pcm_hw_params_set_rate_near (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*,int*) ; 
 scalar_t__ snd_pcm_sw_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_sw_params_alloca (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snd_pcm_sw_params_current (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_sw_params_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_pcm_sw_params_set_avail_min (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_pcm_sw_params_set_start_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_pcm_sw_params_set_stop_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

int ai_alsa_setup(audio_in_t *ai)
{
    snd_pcm_hw_params_t *params;
    snd_pcm_sw_params_t *swparams;
    snd_pcm_uframes_t buffer_size, period_size;
    int err;
    int dir;
    unsigned int rate;

    snd_pcm_hw_params_alloca(&params);
    snd_pcm_sw_params_alloca(&swparams);

    err = snd_pcm_hw_params_any(ai->alsa.handle, params);
    if (err < 0) {
        MP_ERR(ai, "Broken configuration for this PCM: no configurations available.\n");
        return -1;
    }

    err = snd_pcm_hw_params_set_access(ai->alsa.handle, params,
                                       SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0) {
        MP_ERR(ai, "Access type not available.\n");
        return -1;
    }

    err = snd_pcm_hw_params_set_format(ai->alsa.handle, params, SND_PCM_FORMAT_S16);
    if (err < 0) {
        MP_ERR(ai, "Sample format not available.\n");
        return -1;
    }

    err = snd_pcm_hw_params_set_channels(ai->alsa.handle, params, ai->req_channels);
    if (err < 0) {
        snd_pcm_hw_params_get_channels(params, &ai->channels);
        MP_ERR(ai, "Channel count not available - reverting to default: %d\n",
               ai->channels);
    } else {
        ai->channels = ai->req_channels;
    }

    dir = 0;
    rate = ai->req_samplerate;
    err = snd_pcm_hw_params_set_rate_near(ai->alsa.handle, params, &rate, &dir);
    if (err < 0) {
        MP_ERR(ai, "Cannot set samplerate.\n");
    }
    ai->samplerate = rate;

    dir = 0;
    ai->alsa.buffer_time = 1000000;
    err = snd_pcm_hw_params_set_buffer_time_near(ai->alsa.handle, params,
                                                 &ai->alsa.buffer_time, &dir);
    if (err < 0) {
        MP_ERR(ai, "Cannot set buffer time.\n");
    }

    dir = 0;
    ai->alsa.period_time = ai->alsa.buffer_time / 4;
    err = snd_pcm_hw_params_set_period_time_near(ai->alsa.handle, params,
                                                 &ai->alsa.period_time, &dir);
    if (err < 0) {
        MP_ERR(ai, "Cannot set period time.\n");
    }

    err = snd_pcm_hw_params(ai->alsa.handle, params);
    if (err < 0) {
        MP_ERR(ai, "Unable to install hardware parameters: %s", snd_strerror(err));
        snd_pcm_hw_params_dump(params, ai->alsa.log);
        return -1;
    }

    dir = -1;
    snd_pcm_hw_params_get_period_size(params, &period_size, &dir);
    snd_pcm_hw_params_get_buffer_size(params, &buffer_size);
    ai->alsa.chunk_size = period_size;
    if (period_size == buffer_size) {
        MP_ERR(ai, "Can't use period equal to buffer size (%u == %lu)\n", ai->alsa.chunk_size, (long)buffer_size);
        return -1;
    }

    snd_pcm_sw_params_current(ai->alsa.handle, swparams);
    err = snd_pcm_sw_params_set_avail_min(ai->alsa.handle, swparams, ai->alsa.chunk_size);

    err = snd_pcm_sw_params_set_start_threshold(ai->alsa.handle, swparams, 0);
    err = snd_pcm_sw_params_set_stop_threshold(ai->alsa.handle, swparams, buffer_size);

    if (snd_pcm_sw_params(ai->alsa.handle, swparams) < 0) {
        MP_ERR(ai, "Unable to install software parameters:\n");
        snd_pcm_sw_params_dump(swparams, ai->alsa.log);
        return -1;
    }

    if (mp_msg_test(ai->log, MSGL_V)) {
        snd_pcm_dump(ai->alsa.handle, ai->alsa.log);
    }

    ai->alsa.bits_per_sample = snd_pcm_format_physical_width(SND_PCM_FORMAT_S16);
    ai->alsa.bits_per_frame = ai->alsa.bits_per_sample * ai->channels;
    ai->blocksize = ai->alsa.chunk_size * ai->alsa.bits_per_frame / 8;
    ai->samplesize = ai->alsa.bits_per_sample;
    ai->bytes_per_sample = ai->alsa.bits_per_sample/8;

    return 0;
}