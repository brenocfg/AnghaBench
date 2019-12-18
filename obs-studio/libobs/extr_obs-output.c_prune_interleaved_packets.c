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
struct encoder_packet {scalar_t__ type; int /*<<< orphan*/  dts_usec; scalar_t__ track_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  discard_to_idx (struct obs_output*,size_t) ; 
 size_t get_interleaved_start_idx (struct obs_output*) ; 
 int prune_premature_packets (struct obs_output*) ; 

__attribute__((used)) static bool prune_interleaved_packets(struct obs_output *output)
{
	size_t start_idx = 0;
	int prune_start = prune_premature_packets(output);

#if DEBUG_STARTING_PACKETS == 1
	blog(LOG_DEBUG, "--------- Pruning! %d ---------", prune_start);
	for (size_t i = 0; i < output->interleaved_packets.num; i++) {
		struct encoder_packet *packet =
			&output->interleaved_packets.array[i];
		blog(LOG_DEBUG, "packet: %s %d, ts: %lld, pruned = %s",
		     packet->type == OBS_ENCODER_AUDIO ? "audio" : "video",
		     (int)packet->track_idx, packet->dts_usec,
		     (int)i < prune_start ? "true" : "false");
	}
#endif

	/* prunes the first video packet if it's too far away from audio */
	if (prune_start == -1)
		return false;
	else if (prune_start != 0)
		start_idx = (size_t)prune_start;
	else
		start_idx = get_interleaved_start_idx(output);

	if (start_idx)
		discard_to_idx(output, start_idx);

	return true;
}