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
struct TYPE_3__ {float** prev_samples; } ;
typedef  TYPE_1__ obs_volmeter_t ;

/* Variables and functions */

__attribute__((used)) static void volmeter_process_peak_last_samples(obs_volmeter_t *volmeter,
		int channel_nr, float *samples, size_t nr_samples)
{
	/* Take the last 4 samples that need to be used for the next peak
	 * calculation. If there are less than 4 samples in total the new
	 * samples shift out the old samples. */

	switch (nr_samples) {
	case 0:
		break;
	case 1:
		volmeter->prev_samples[channel_nr][0] =
				volmeter->prev_samples[channel_nr][1];
		volmeter->prev_samples[channel_nr][1] =
				volmeter->prev_samples[channel_nr][2];
		volmeter->prev_samples[channel_nr][2] =
				volmeter->prev_samples[channel_nr][3];
		volmeter->prev_samples[channel_nr][3] = samples[nr_samples-1];
		break;
	case 2:
		volmeter->prev_samples[channel_nr][0] =
				volmeter->prev_samples[channel_nr][2];
		volmeter->prev_samples[channel_nr][1] =
				volmeter->prev_samples[channel_nr][3];
		volmeter->prev_samples[channel_nr][2] = samples[nr_samples-2];
		volmeter->prev_samples[channel_nr][3] = samples[nr_samples-1];
		break;
	case 3:
		volmeter->prev_samples[channel_nr][0] =
				volmeter->prev_samples[channel_nr][3];
		volmeter->prev_samples[channel_nr][1] = samples[nr_samples-3];
		volmeter->prev_samples[channel_nr][2] = samples[nr_samples-2];
		volmeter->prev_samples[channel_nr][3] = samples[nr_samples-1];
		break;
	default:
		volmeter->prev_samples[channel_nr][0] = samples[nr_samples-4];
		volmeter->prev_samples[channel_nr][1] = samples[nr_samples-3];
		volmeter->prev_samples[channel_nr][2] = samples[nr_samples-2];
		volmeter->prev_samples[channel_nr][3] = samples[nr_samples-1];
	}
}