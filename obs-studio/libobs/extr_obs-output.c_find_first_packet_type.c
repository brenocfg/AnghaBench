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
struct obs_output {TYPE_1__ interleaved_packets; } ;
struct encoder_packet {int dummy; } ;
typedef  enum obs_encoder_type { ____Placeholder_obs_encoder_type } obs_encoder_type ;

/* Variables and functions */
 int find_first_packet_type_idx (struct obs_output*,int,size_t) ; 

__attribute__((used)) static inline struct encoder_packet *
find_first_packet_type(struct obs_output *output, enum obs_encoder_type type,
		       size_t audio_idx)
{
	int idx = find_first_packet_type_idx(output, type, audio_idx);
	return (idx != -1) ? &output->interleaved_packets.array[idx] : NULL;
}