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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct pause_data {int ts_end; int ts_start; } ;
struct audio_data {int timestamp; scalar_t__ frames; scalar_t__* data; } ;

/* Variables and functions */
 size_t MAX_AV_PLANES ; 
 int ns_to_audio_frames (size_t,int) ; 

__attribute__((used)) static void unpause_audio(struct pause_data *pause, struct audio_data *data,
			  size_t sample_rate)
{
	uint64_t cutoff_frames = pause->ts_end - data->timestamp;
	cutoff_frames = ns_to_audio_frames(sample_rate, cutoff_frames);

	for (size_t i = 0; i < MAX_AV_PLANES; i++) {
		if (!data->data[i])
			break;
		data->data[i] += cutoff_frames * sizeof(float);
	}

	data->timestamp = pause->ts_start;
	data->frames = data->frames - (uint32_t)cutoff_frames;
	pause->ts_start = 0;
	pause->ts_end = 0;
}