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
struct encoder_packet {scalar_t__ dts_usec; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  discard_to_idx (struct obs_output*,size_t) ; 

__attribute__((used)) static void discard_unused_audio_packets(struct obs_output *output,
					 int64_t dts_usec)
{
	size_t idx = 0;

	for (; idx < output->interleaved_packets.num; idx++) {
		struct encoder_packet *p =
			&output->interleaved_packets.array[idx];

		if (p->dts_usec >= dts_usec)
			break;
	}

	if (idx)
		discard_to_idx(output, idx);
}