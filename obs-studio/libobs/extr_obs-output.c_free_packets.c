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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct obs_output {TYPE_1__ interleaved_packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (scalar_t__) ; 

__attribute__((used)) static inline void free_packets(struct obs_output *output)
{
	for (size_t i = 0; i < output->interleaved_packets.num; i++)
		obs_encoder_packet_release(output->interleaved_packets.array +
					   i);
	da_free(output->interleaved_packets);
}