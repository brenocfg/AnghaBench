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
struct obs_output {scalar_t__* audio_offsets; scalar_t__ video_offset; } ;
struct encoder_packet {scalar_t__ type; size_t track_idx; int /*<<< orphan*/  dts_usec; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  packet_dts_usec (struct encoder_packet*) ; 

__attribute__((used)) static inline void apply_interleaved_packet_offset(struct obs_output *output,
						   struct encoder_packet *out)
{
	int64_t offset;

	/* audio and video need to start at timestamp 0, and the encoders
	 * may not currently be at 0 when we get data.  so, we store the
	 * current dts as offset and subtract that value from the dts/pts
	 * of the output packet. */
	offset = (out->type == OBS_ENCODER_VIDEO)
			 ? output->video_offset
			 : output->audio_offsets[out->track_idx];

	out->dts -= offset;
	out->pts -= offset;

	/* convert the newly adjusted dts to relative dts time to ensure proper
	 * interleaving.  if we're using an audio encoder that's already been
	 * started on another output, then the first audio packet may not be
	 * quite perfectly synced up in terms of system time (and there's
	 * nothing we can really do about that), but it will always at least be
	 * within a 23ish millisecond threshold (at least for AAC) */
	out->dts_usec = packet_dts_usec(out);
}