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
 int /*<<< orphan*/  allocate_counters (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  allocate_fd_percpu () ; 
 int /*<<< orphan*/  allocate_irq_buffers () ; 
 int /*<<< orphan*/  allocate_output_buffer () ; 
 int /*<<< orphan*/  core_even ; 
 int /*<<< orphan*/  core_odd ; 
 int /*<<< orphan*/  for_all_proc_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_counters ; 
 int /*<<< orphan*/  package_even ; 
 int /*<<< orphan*/  package_odd ; 
 int /*<<< orphan*/  thread_even ; 
 int /*<<< orphan*/  thread_odd ; 
 int /*<<< orphan*/  topology_probe () ; 

void setup_all_buffers(void)
{
	topology_probe();
	allocate_irq_buffers();
	allocate_fd_percpu();
	allocate_counters(&thread_even, &core_even, &package_even);
	allocate_counters(&thread_odd, &core_odd, &package_odd);
	allocate_output_buffer();
	for_all_proc_cpus(initialize_counters);
}