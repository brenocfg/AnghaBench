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
struct tc_netem_slot {scalar_t__ max_packets; scalar_t__ max_bytes; int min_delay; int max_delay; int dist_jitter; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {scalar_t__ packets_left; scalar_t__ bytes_left; scalar_t__ slot_next; } ;
struct netem_sched_data {TYPE_1__ slot; struct tc_netem_slot slot_config; } ;

/* Variables and functions */
 void* INT_MAX ; 
 scalar_t__ ktime_get_ns () ; 
 struct tc_netem_slot* nla_data (struct nlattr const*) ; 

__attribute__((used)) static void get_slot(struct netem_sched_data *q, const struct nlattr *attr)
{
	const struct tc_netem_slot *c = nla_data(attr);

	q->slot_config = *c;
	if (q->slot_config.max_packets == 0)
		q->slot_config.max_packets = INT_MAX;
	if (q->slot_config.max_bytes == 0)
		q->slot_config.max_bytes = INT_MAX;
	q->slot.packets_left = q->slot_config.max_packets;
	q->slot.bytes_left = q->slot_config.max_bytes;
	if (q->slot_config.min_delay | q->slot_config.max_delay |
	    q->slot_config.dist_jitter)
		q->slot.slot_next = ktime_get_ns();
	else
		q->slot.slot_next = 0;
}