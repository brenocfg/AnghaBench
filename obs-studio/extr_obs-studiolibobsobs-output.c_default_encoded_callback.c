#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* encoded_packet ) (int /*<<< orphan*/ ,struct encoder_packet*) ;} ;
struct obs_output {scalar_t__ active_delay_ns; int /*<<< orphan*/  total_frames; TYPE_2__ context; TYPE_1__ info; } ;
struct encoder_packet {scalar_t__ type; int /*<<< orphan*/  track_idx; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_AUDIO ; 
 scalar_t__ OBS_ENCODER_VIDEO ; 
 scalar_t__ data_active (struct obs_output*) ; 
 int /*<<< orphan*/  get_track_index (struct obs_output*,struct encoder_packet*) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (struct encoder_packet*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct encoder_packet*) ; 

__attribute__((used)) static void default_encoded_callback(void *param, struct encoder_packet *packet)
{
	struct obs_output *output = param;

	if (data_active(output)) {
		if (packet->type == OBS_ENCODER_AUDIO)
			packet->track_idx = get_track_index(output, packet);

		output->info.encoded_packet(output->context.data, packet);

		if (packet->type == OBS_ENCODER_VIDEO)
			output->total_frames++;
	}

	if (output->active_delay_ns)
		obs_encoder_packet_release(packet);
}