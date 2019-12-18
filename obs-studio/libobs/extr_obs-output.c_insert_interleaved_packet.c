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
struct encoder_packet {scalar_t__ dts_usec; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  da_insert (TYPE_1__,size_t,struct encoder_packet*) ; 

__attribute__((used)) static inline void insert_interleaved_packet(struct obs_output *output,
					     struct encoder_packet *out)
{
	size_t idx;
	for (idx = 0; idx < output->interleaved_packets.num; idx++) {
		struct encoder_packet *cur_packet;
		cur_packet = output->interleaved_packets.array + idx;

		if (out->dts_usec == cur_packet->dts_usec &&
		    out->type == OBS_ENCODER_VIDEO) {
			break;
		} else if (out->dts_usec < cur_packet->dts_usec) {
			break;
		}
	}

	da_insert(output->interleaved_packets, idx, out);
}