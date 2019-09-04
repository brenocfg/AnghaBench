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
struct obs_output {scalar_t__ highest_audio_ts; scalar_t__ highest_video_ts; } ;
struct encoder_packet {scalar_t__ type; scalar_t__ dts_usec; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 

__attribute__((used)) static inline bool has_higher_opposing_ts(struct obs_output *output,
		struct encoder_packet *packet)
{
	if (packet->type == OBS_ENCODER_VIDEO)
		return output->highest_audio_ts > packet->dts_usec;
	else
		return output->highest_video_ts > packet->dts_usec;
}