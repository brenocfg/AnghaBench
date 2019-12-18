#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct encoder_packet* array; } ;
struct obs_output {int received_video; int received_audio; TYPE_1__ interleaved_packets; } ;
struct encoder_packet {long long timebase_num; long long timebase_den; scalar_t__ dts_usec; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  OBS_ENCODER_VIDEO ; 
 int find_first_packet_type_idx (struct obs_output*,int /*<<< orphan*/ ,size_t) ; 
 size_t num_audio_mixes (struct obs_output*) ; 

__attribute__((used)) static int prune_premature_packets(struct obs_output *output)
{
	size_t audio_mixes = num_audio_mixes(output);
	struct encoder_packet *video;
	int video_idx;
	int max_idx;
	int64_t duration_usec;
	int64_t max_diff = 0;
	int64_t diff = 0;

	video_idx = find_first_packet_type_idx(output, OBS_ENCODER_VIDEO, 0);
	if (video_idx == -1) {
		output->received_video = false;
		return -1;
	}

	max_idx = video_idx;
	video = &output->interleaved_packets.array[video_idx];
	duration_usec = video->timebase_num * 1000000LL / video->timebase_den;

	for (size_t i = 0; i < audio_mixes; i++) {
		struct encoder_packet *audio;
		int audio_idx;

		audio_idx = find_first_packet_type_idx(output,
						       OBS_ENCODER_AUDIO, i);
		if (audio_idx == -1) {
			output->received_audio = false;
			return -1;
		}

		audio = &output->interleaved_packets.array[audio_idx];
		if (audio_idx > max_idx)
			max_idx = audio_idx;

		diff = audio->dts_usec - video->dts_usec;
		if (diff > max_diff)
			max_diff = diff;
	}

	return diff > duration_usec ? max_idx + 1 : 0;
}