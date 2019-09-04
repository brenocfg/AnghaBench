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
struct evtchn_fifo_control_block {int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHN_FIFO_MAX_QUEUES ; 
 int /*<<< orphan*/  consume_one_event (unsigned int,struct evtchn_fifo_control_block*,unsigned int,unsigned long*,int) ; 
 int /*<<< orphan*/  cpu_control_block ; 
 unsigned int find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 struct evtchn_fifo_control_block* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __evtchn_fifo_handle_events(unsigned cpu, bool drop)
{
	struct evtchn_fifo_control_block *control_block;
	unsigned long ready;
	unsigned q;

	control_block = per_cpu(cpu_control_block, cpu);

	ready = xchg(&control_block->ready, 0);

	while (ready) {
		q = find_first_bit(&ready, EVTCHN_FIFO_MAX_QUEUES);
		consume_one_event(cpu, control_block, q, &ready, drop);
		ready |= xchg(&control_block->ready, 0);
	}
}