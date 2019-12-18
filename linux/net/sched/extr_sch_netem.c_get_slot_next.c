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
typedef  int u64 ;
struct TYPE_4__ {int min_delay; int max_delay; int /*<<< orphan*/  max_bytes; int /*<<< orphan*/  max_packets; scalar_t__ dist_jitter; int /*<<< orphan*/  dist_delay; } ;
struct TYPE_3__ {int slot_next; int /*<<< orphan*/  bytes_left; int /*<<< orphan*/  packets_left; } ;
struct netem_sched_data {TYPE_2__ slot_config; TYPE_1__ slot; int /*<<< orphan*/  slot_dist; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int prandom_u32 () ; 
 int tabledist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_slot_next(struct netem_sched_data *q, u64 now)
{
	s64 next_delay;

	if (!q->slot_dist)
		next_delay = q->slot_config.min_delay +
				(prandom_u32() *
				 (q->slot_config.max_delay -
				  q->slot_config.min_delay) >> 32);
	else
		next_delay = tabledist(q->slot_config.dist_delay,
				       (s32)(q->slot_config.dist_jitter),
				       NULL, q->slot_dist);

	q->slot.slot_next = now + next_delay;
	q->slot.packets_left = q->slot_config.max_packets;
	q->slot.bytes_left = q->slot_config.max_bytes;
}