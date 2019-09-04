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
 int /*<<< orphan*/  cpu_control_block ; 
 int evtchn_fifo_alloc_control_block (unsigned int) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xen_evtchn_cpu_prepare(unsigned int cpu)
{
	if (!per_cpu(cpu_control_block, cpu))
		return evtchn_fifo_alloc_control_block(cpu);
	return 0;
}