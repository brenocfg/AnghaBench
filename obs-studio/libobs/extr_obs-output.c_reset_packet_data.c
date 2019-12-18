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
struct TYPE_4__ {int received_audio; int received_video; scalar_t__* audio_offsets; scalar_t__ video_offset; scalar_t__ highest_video_ts; scalar_t__ highest_audio_ts; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  free_packets (TYPE_1__*) ; 

__attribute__((used)) static void reset_packet_data(obs_output_t *output)
{
	output->received_audio = false;
	output->received_video = false;
	output->highest_audio_ts = 0;
	output->highest_video_ts = 0;
	output->video_offset = 0;

	for (size_t i = 0; i < MAX_AUDIO_MIXES; i++)
		output->audio_offsets[i] = 0;

	free_packets(output);
}