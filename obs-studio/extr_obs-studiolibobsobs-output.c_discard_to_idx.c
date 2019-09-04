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

/* Variables and functions */
 int /*<<< orphan*/  da_erase_range (TYPE_1__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (struct encoder_packet*) ; 

__attribute__((used)) static void discard_to_idx(struct obs_output *output, size_t idx)
{
	for (size_t i = 0; i < idx; i++) {
		struct encoder_packet *packet =
			&output->interleaved_packets.array[i];
		obs_encoder_packet_release(packet);
	}

	da_erase_range(output->interleaved_packets, 0, idx);
}