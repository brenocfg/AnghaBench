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
typedef  size_t uint32_t ;
struct compressor_data {float ratio; float threshold; size_t num_channels; size_t sample_rate; float slope; char const* sidechain_name; scalar_t__ envelope_buf_len; int /*<<< orphan*/  sidechain_update_mutex; scalar_t__ sidechain_check_time; int /*<<< orphan*/ * weak_sidechain; int /*<<< orphan*/  output_gain; void* release_gain; void* attack_gain; } ;
typedef  int /*<<< orphan*/  obs_weak_source_t ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 size_t const DEFAULT_AUDIO_BUF_MS ; 
 size_t const MS_IN_S ; 
 float const MS_IN_S_F ; 
 int /*<<< orphan*/  S_ATTACK_TIME ; 
 int /*<<< orphan*/  S_OUTPUT_GAIN ; 
 int /*<<< orphan*/  S_RATIO ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  S_SIDECHAIN_SOURCE ; 
 int /*<<< orphan*/  S_THRESHOLD ; 
 size_t audio_output_get_channels (int /*<<< orphan*/ ) ; 
 size_t audio_output_get_sample_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (char const*) ; 
 char const* bstrdup (char const*) ; 
 int /*<<< orphan*/  db_to_mul (float const) ; 
 void* gain_coefficient (size_t const,float const) ; 
 scalar_t__ obs_data_get_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_get_audio () ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_remove_audio_capture_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct compressor_data*) ; 
 int /*<<< orphan*/ * obs_weak_source_get_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_weak_source_release (int /*<<< orphan*/ *) ; 
 scalar_t__ os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resize_env_buffer (struct compressor_data*,size_t) ; 
 int /*<<< orphan*/  sidechain_capture ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void compressor_update(void *data, obs_data_t *s)
{
	struct compressor_data *cd = data;

	const uint32_t sample_rate =
		audio_output_get_sample_rate(obs_get_audio());
	const size_t num_channels = audio_output_get_channels(obs_get_audio());
	const float attack_time_ms = (float)obs_data_get_int(s, S_ATTACK_TIME);
	const float release_time_ms =
		(float)obs_data_get_int(s, S_RELEASE_TIME);
	const float output_gain_db =
		(float)obs_data_get_double(s, S_OUTPUT_GAIN);
	const char *sidechain_name = obs_data_get_string(s, S_SIDECHAIN_SOURCE);

	cd->ratio = (float)obs_data_get_double(s, S_RATIO);
	cd->threshold = (float)obs_data_get_double(s, S_THRESHOLD);
	cd->attack_gain =
		gain_coefficient(sample_rate, attack_time_ms / MS_IN_S_F);
	cd->release_gain =
		gain_coefficient(sample_rate, release_time_ms / MS_IN_S_F);
	cd->output_gain = db_to_mul(output_gain_db);
	cd->num_channels = num_channels;
	cd->sample_rate = sample_rate;
	cd->slope = 1.0f - (1.0f / cd->ratio);

	bool valid_sidechain = *sidechain_name &&
			       strcmp(sidechain_name, "none") != 0;
	obs_weak_source_t *old_weak_sidechain = NULL;

	pthread_mutex_lock(&cd->sidechain_update_mutex);

	if (!valid_sidechain) {
		if (cd->weak_sidechain) {
			old_weak_sidechain = cd->weak_sidechain;
			cd->weak_sidechain = NULL;
		}

		bfree(cd->sidechain_name);
		cd->sidechain_name = NULL;

	} else {
		if (!cd->sidechain_name ||
		    strcmp(cd->sidechain_name, sidechain_name) != 0) {
			if (cd->weak_sidechain) {
				old_weak_sidechain = cd->weak_sidechain;
				cd->weak_sidechain = NULL;
			}

			bfree(cd->sidechain_name);
			cd->sidechain_name = bstrdup(sidechain_name);
			cd->sidechain_check_time = os_gettime_ns() - 3000000000;
		}
	}

	pthread_mutex_unlock(&cd->sidechain_update_mutex);

	if (old_weak_sidechain) {
		obs_source_t *old_sidechain =
			obs_weak_source_get_source(old_weak_sidechain);

		if (old_sidechain) {
			obs_source_remove_audio_capture_callback(
				old_sidechain, sidechain_capture, cd);
			obs_source_release(old_sidechain);
		}

		obs_weak_source_release(old_weak_sidechain);
	}

	size_t sample_len = sample_rate * DEFAULT_AUDIO_BUF_MS / MS_IN_S;
	if (cd->envelope_buf_len == 0)
		resize_env_buffer(cd, sample_len);
}