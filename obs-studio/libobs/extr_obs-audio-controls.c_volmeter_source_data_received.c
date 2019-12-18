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
struct obs_volmeter {float* magnitude; float* peak; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cur_db; } ;
struct audio_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int MAX_AUDIO_CHANNELS ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 float db_to_mul (int /*<<< orphan*/ ) ; 
 float mul_to_db (float) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_levels_updated (struct obs_volmeter*,float*,float*,float*) ; 
 int /*<<< orphan*/  volmeter_process_audio_data (struct obs_volmeter*,struct audio_data const*) ; 

__attribute__((used)) static void volmeter_source_data_received(void *vptr, obs_source_t *source,
					  const struct audio_data *data,
					  bool muted)
{
	struct obs_volmeter *volmeter = (struct obs_volmeter *)vptr;
	float mul;
	float magnitude[MAX_AUDIO_CHANNELS];
	float peak[MAX_AUDIO_CHANNELS];
	float input_peak[MAX_AUDIO_CHANNELS];

	pthread_mutex_lock(&volmeter->mutex);

	volmeter_process_audio_data(volmeter, data);

	// Adjust magnitude/peak based on the volume level set by the user.
	// And convert to dB.
	mul = muted ? 0.0f : db_to_mul(volmeter->cur_db);
	for (int channel_nr = 0; channel_nr < MAX_AUDIO_CHANNELS;
	     channel_nr++) {
		magnitude[channel_nr] =
			mul_to_db(volmeter->magnitude[channel_nr] * mul);
		peak[channel_nr] = mul_to_db(volmeter->peak[channel_nr] * mul);

		/* The input-peak is NOT adjusted with volume, so that the user
		 * can check the input-gain. */
		input_peak[channel_nr] = mul_to_db(volmeter->peak[channel_nr]);
	}

	pthread_mutex_unlock(&volmeter->mutex);

	signal_levels_updated(volmeter, magnitude, peak, input_peak);

	UNUSED_PARAMETER(source);
}