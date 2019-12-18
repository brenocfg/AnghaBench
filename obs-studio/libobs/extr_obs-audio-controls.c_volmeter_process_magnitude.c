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
struct audio_data {size_t frames; scalar_t__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * magnitude; } ;
typedef  TYPE_1__ obs_volmeter_t ;

/* Variables and functions */
 int /*<<< orphan*/  sqrtf (float) ; 

__attribute__((used)) static void volmeter_process_magnitude(obs_volmeter_t *volmeter,
				       const struct audio_data *data,
				       int nr_channels)
{
	size_t nr_samples = data->frames;

	int channel_nr = 0;
	for (int plane_nr = 0; channel_nr < nr_channels; plane_nr++) {
		float *samples = (float *)data->data[plane_nr];
		if (!samples) {
			continue;
		}

		float sum = 0.0;
		for (size_t i = 0; i < nr_samples; i++) {
			float sample = samples[i];
			sum += sample * sample;
		}
		volmeter->magnitude[channel_nr] = sqrtf(sum / nr_samples);

		channel_nr++;
	}
}