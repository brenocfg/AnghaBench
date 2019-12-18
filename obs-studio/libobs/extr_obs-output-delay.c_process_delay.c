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
typedef  int /*<<< orphan*/  uint64_t ;
struct obs_output {int dummy; } ;
struct encoder_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_gettime_ns () ; 
 scalar_t__ pop_packet (struct obs_output*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_packet (struct obs_output*,struct encoder_packet*,int /*<<< orphan*/ ) ; 

void process_delay(void *data, struct encoder_packet *packet)
{
	struct obs_output *output = data;
	uint64_t t = os_gettime_ns();
	push_packet(output, packet, t);
	while (pop_packet(output, t))
		;
}