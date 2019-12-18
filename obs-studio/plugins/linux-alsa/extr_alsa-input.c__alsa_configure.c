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
struct alsa_data {int channels; int period_size; int sample_size; scalar_t__ buffer; int /*<<< orphan*/  format; int /*<<< orphan*/  handle; int /*<<< orphan*/  device; int /*<<< orphan*/  rate; } ;
typedef  int /*<<< orphan*/  snd_pcm_hw_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SND_PCM_ACCESS_RW_INTERLEAVED ; 
 int /*<<< orphan*/  SND_PCM_FORMAT_S16 ; 
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ bzalloc (int) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_params_alloca (int /*<<< orphan*/ **) ; 
 int snd_pcm_hw_params_any (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_pcm_hw_params_get_channels (int /*<<< orphan*/ *,int*) ; 
 int snd_pcm_hw_params_get_period_size (int /*<<< orphan*/ *,int*,int*) ; 
 int snd_pcm_hw_params_set_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params_set_channels_near (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int snd_pcm_hw_params_set_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params_set_rate_near (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

bool _alsa_configure(struct alsa_data *data)
{
	snd_pcm_hw_params_t *hwparams;
	int err;
	int dir;

	snd_pcm_hw_params_alloca(&hwparams);

	err = snd_pcm_hw_params_any(data->handle, hwparams);
	if (err < 0) {
		blog(LOG_ERROR, "snd_pcm_hw_params_any failed: %s",
		     snd_strerror(err));
		return false;
	}

	err = snd_pcm_hw_params_set_access(data->handle, hwparams,
					   SND_PCM_ACCESS_RW_INTERLEAVED);
	if (err < 0) {
		blog(LOG_ERROR, "snd_pcm_hw_params_set_access failed: %s",
		     snd_strerror(err));
		return false;
	}

	data->format = SND_PCM_FORMAT_S16;
	err = snd_pcm_hw_params_set_format(data->handle, hwparams,
					   data->format);
	if (err < 0) {
		blog(LOG_ERROR, "snd_pcm_hw_params_set_format failed: %s",
		     snd_strerror(err));
		return false;
	}

	err = snd_pcm_hw_params_set_rate_near(data->handle, hwparams,
					      &data->rate, 0);
	if (err < 0) {
		blog(LOG_ERROR, "snd_pcm_hw_params_set_rate_near failed: %s",
		     snd_strerror(err));
		return false;
	}
	blog(LOG_INFO, "PCM '%s' rate set to %d", data->device, data->rate);

	err = snd_pcm_hw_params_get_channels(hwparams, &data->channels);
	if (err < 0)
		data->channels = 2;

	err = snd_pcm_hw_params_set_channels_near(data->handle, hwparams,
						  &data->channels);
	if (err < 0) {
		blog(LOG_ERROR,
		     "snd_pcm_hw_params_set_channels_near failed: %s",
		     snd_strerror(err));
		return false;
	}
	blog(LOG_INFO, "PCM '%s' channels set to %d", data->device,
	     data->channels);

	err = snd_pcm_hw_params(data->handle, hwparams);
	if (err < 0) {
		blog(LOG_ERROR, "snd_pcm_hw_params failed: %s",
		     snd_strerror(err));
		return false;
	}

	err = snd_pcm_hw_params_get_period_size(hwparams, &data->period_size,
						&dir);
	if (err < 0) {
		blog(LOG_ERROR, "snd_pcm_hw_params_get_period_size failed: %s",
		     snd_strerror(err));
		return false;
	}

	data->sample_size =
		(data->channels * snd_pcm_format_physical_width(data->format)) /
		8;

	if (data->buffer)
		bfree(data->buffer);
	data->buffer = bzalloc(data->period_size * data->sample_size);

	return true;
}