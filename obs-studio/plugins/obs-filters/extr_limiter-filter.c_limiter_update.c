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
struct limiter_data {float threshold; size_t num_channels; size_t sample_rate; float slope; scalar_t__ envelope_buf_len; int /*<<< orphan*/  output_gain; void* release_gain; void* attack_gain; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 float ATK_TIME ; 
 size_t const DEFAULT_AUDIO_BUF_MS ; 
 size_t const MS_IN_S ; 
 float MS_IN_S_F ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  S_THRESHOLD ; 
 size_t audio_output_get_channels (int /*<<< orphan*/ ) ; 
 size_t audio_output_get_sample_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_to_mul (float const) ; 
 void* gain_coefficient (size_t const,float const) ; 
 scalar_t__ obs_data_get_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_get_audio () ; 
 int /*<<< orphan*/  resize_env_buffer (struct limiter_data*,size_t) ; 

__attribute__((used)) static void limiter_update(void *data, obs_data_t *s)
{
	struct limiter_data *cd = data;

	const uint32_t sample_rate =
		audio_output_get_sample_rate(obs_get_audio());
	const size_t num_channels = audio_output_get_channels(obs_get_audio());
	float attack_time_ms = ATK_TIME;

	const float release_time_ms =
		(float)obs_data_get_int(s, S_RELEASE_TIME);
	const float output_gain_db = 0;

	cd->threshold = (float)obs_data_get_double(s, S_THRESHOLD);

	cd->attack_gain =
		gain_coefficient(sample_rate, attack_time_ms / MS_IN_S_F);
	cd->release_gain =
		gain_coefficient(sample_rate, release_time_ms / MS_IN_S_F);
	cd->output_gain = db_to_mul(output_gain_db);
	cd->num_channels = num_channels;
	cd->sample_rate = sample_rate;
	cd->slope = 1.0f;

	size_t sample_len = sample_rate * DEFAULT_AUDIO_BUF_MS / MS_IN_S;
	if (cd->envelope_buf_len == 0)
		resize_env_buffer(cd, sample_len);
}