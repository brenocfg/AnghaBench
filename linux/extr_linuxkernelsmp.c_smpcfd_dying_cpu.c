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

/* Variables and functions */
 int /*<<< orphan*/  flush_smp_call_function_queue (int) ; 

int smpcfd_dying_cpu(unsigned int cpu)
{
	/*
	 * The IPIs for the smp-call-function callbacks queued by other
	 * CPUs might arrive late, either due to hardware latencies or
	 * because this CPU disabled interrupts (inside stop-machine)
	 * before the IPIs were sent. So flush out any pending callbacks
	 * explicitly (without waiting for the IPIs to arrive), to
	 * ensure that the outgoing CPU doesn't go offline with work
	 * still pending.
	 */
	flush_smp_call_function_queue(false);
	return 0;
}