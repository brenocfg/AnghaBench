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
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  pts; } ;
struct ff_packet {TYPE_1__ base; } ;
struct ff_decoder {int /*<<< orphan*/  clock; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ ff_clock_start_time (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_decoder_set_frame_drop_state (struct ff_decoder*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shrink_packet (struct ff_packet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_late_packets(struct ff_decoder *decoder,
                              struct ff_packet *packet)
{
	int64_t start_time = ff_clock_start_time(decoder->clock);
	if (start_time != AV_NOPTS_VALUE) {
		if (ff_decoder_set_frame_drop_state(decoder, start_time,
		                                    packet->base.pts))
			shrink_packet(packet, packet->base.size);
	}
}