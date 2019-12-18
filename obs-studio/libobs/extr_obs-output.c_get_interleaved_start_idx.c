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
struct TYPE_2__ {size_t num; struct encoder_packet* array; } ;
struct obs_output {TYPE_1__ interleaved_packets; } ;
struct encoder_packet {scalar_t__ type; scalar_t__ dts_usec; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 scalar_t__ OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  OBS_ENCODER_VIDEO ; 
 struct encoder_packet* find_first_packet_type (struct obs_output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ llabs (scalar_t__) ; 

__attribute__((used)) static size_t get_interleaved_start_idx(struct obs_output *output)
{
	int64_t closest_diff = 0x7FFFFFFFFFFFFFFFLL;
	struct encoder_packet *first_video =
		find_first_packet_type(output, OBS_ENCODER_VIDEO, 0);
	size_t video_idx = DARRAY_INVALID;
	size_t idx = 0;

	for (size_t i = 0; i < output->interleaved_packets.num; i++) {
		struct encoder_packet *packet =
			&output->interleaved_packets.array[i];
		int64_t diff;

		if (packet->type != OBS_ENCODER_AUDIO) {
			if (packet == first_video)
				video_idx = i;
			continue;
		}

		diff = llabs(packet->dts_usec - first_video->dts_usec);
		if (diff < closest_diff) {
			closest_diff = diff;
			idx = i;
		}
	}

	return video_idx < idx ? video_idx : idx;
}