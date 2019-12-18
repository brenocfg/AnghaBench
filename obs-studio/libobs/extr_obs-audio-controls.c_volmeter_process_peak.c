#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct audio_data {int frames; scalar_t__* data; } ;
struct TYPE_4__ {double* peak; int peak_meter_type; int /*<<< orphan*/ * prev_samples; } ;
typedef  TYPE_1__ obs_volmeter_t ;
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int MAX_AUDIO_CHANNELS ; 
#define  SAMPLE_PEAK_METER 129 
#define  TRUE_PEAK_METER 128 
 int /*<<< orphan*/  _mm_loadu_ps (int /*<<< orphan*/ ) ; 
 float get_sample_peak (int /*<<< orphan*/ ,float*,int) ; 
 float get_true_peak (int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  printf (char*,int,float*) ; 
 int /*<<< orphan*/  volmeter_process_peak_last_samples (TYPE_1__*,int,float*,int) ; 

__attribute__((used)) static void volmeter_process_peak(obs_volmeter_t *volmeter,
				  const struct audio_data *data,
				  int nr_channels)
{
	int nr_samples = data->frames;
	int channel_nr = 0;
	for (int plane_nr = 0; channel_nr < nr_channels; plane_nr++) {
		float *samples = (float *)data->data[plane_nr];
		if (!samples) {
			continue;
		}
		if (((uintptr_t)samples & 0xf) > 0) {
			printf("Audio plane %i is not aligned %p skipping "
			       "peak volume measurement.\n",
			       plane_nr, samples);
			volmeter->peak[channel_nr] = 1.0;
			channel_nr++;
			continue;
		}

		/* volmeter->prev_samples may not be aligned to 16 bytes;
		 * use unaligned load. */
		__m128 previous_samples =
			_mm_loadu_ps(volmeter->prev_samples[channel_nr]);

		float peak;
		switch (volmeter->peak_meter_type) {
		case TRUE_PEAK_METER:
			peak = get_true_peak(previous_samples, samples,
					     nr_samples);
			break;

		case SAMPLE_PEAK_METER:
		default:
			peak = get_sample_peak(previous_samples, samples,
					       nr_samples);
			break;
		}

		volmeter_process_peak_last_samples(volmeter, channel_nr,
						   samples, nr_samples);

		volmeter->peak[channel_nr] = peak;

		channel_nr++;
	}

	/* Clear the peak of the channels that have not been handled. */
	for (; channel_nr < MAX_AUDIO_CHANNELS; channel_nr++) {
		volmeter->peak[channel_nr] = 0.0;
	}
}