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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
struct sinewave_data {int /*<<< orphan*/  source; int /*<<< orphan*/  event; } ;
struct obs_source_audio {int frames; int samples_per_sec; int timestamp; int /*<<< orphan*/  format; int /*<<< orphan*/  speakers; scalar_t__** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FORMAT_U8BIT ; 
 scalar_t__ EAGAIN ; 
 double M_PI_X2 ; 
 int /*<<< orphan*/  SPEAKERS_MONO ; 
 double cos (double) ; 
 int /*<<< orphan*/  obs_source_output_audio (int /*<<< orphan*/ ,struct obs_source_audio*) ; 
 scalar_t__ os_event_try (int /*<<< orphan*/ ) ; 
 int os_gettime_ns () ; 
 int /*<<< orphan*/  os_sleepto_ns (int) ; 
 double rate ; 

__attribute__((used)) static void *sinewave_thread(void *pdata)
{
	struct sinewave_data *swd = pdata;
	uint64_t last_time = os_gettime_ns();
	uint64_t ts = 0;
	double cos_val = 0.0;
	uint8_t bytes[480];

	while (os_event_try(swd->event) == EAGAIN) {
		if (!os_sleepto_ns(last_time += 10000000))
			last_time = os_gettime_ns();

		for (size_t i = 0; i < 480; i++) {
			cos_val += rate * M_PI_X2;
			if (cos_val > M_PI_X2)
				cos_val -= M_PI_X2;

			double wave = cos(cos_val) * 0.5;
			bytes[i] = (uint8_t)((wave + 1.0) * 0.5 * 255.0);
		}

		struct obs_source_audio data;
		data.data[0] = bytes;
		data.frames = 480;
		data.speakers = SPEAKERS_MONO;
		data.samples_per_sec = 48000;
		data.timestamp = ts;
		data.format = AUDIO_FORMAT_U8BIT;
		obs_source_output_audio(swd->source, &data);

		ts += 10000000;
	}

	return NULL;
}