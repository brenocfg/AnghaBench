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
typedef  int /*<<< orphan*/  u16 ;
struct hsr_port {size_t type; } ;
struct hsr_node {int* time_in_stale; int /*<<< orphan*/ * time_in; int /*<<< orphan*/ * seq_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ seq_nr_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hsr_register_frame_in(struct hsr_node *node, struct hsr_port *port,
			   u16 sequence_nr)
{
	/* Don't register incoming frames without a valid sequence number. This
	 * ensures entries of restarted nodes gets pruned so that they can
	 * re-register and resume communications.
	 */
	if (seq_nr_before(sequence_nr, node->seq_out[port->type]))
		return;

	node->time_in[port->type] = jiffies;
	node->time_in_stale[port->type] = false;
}