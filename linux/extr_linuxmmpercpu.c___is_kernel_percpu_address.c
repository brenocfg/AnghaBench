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

bool __is_kernel_percpu_address(unsigned long addr, unsigned long *can_addr)
{
#ifdef CONFIG_SMP
	const size_t static_size = __per_cpu_end - __per_cpu_start;
	void __percpu *base = __addr_to_pcpu_ptr(pcpu_base_addr);
	unsigned int cpu;

	for_each_possible_cpu(cpu) {
		void *start = per_cpu_ptr(base, cpu);
		void *va = (void *)addr;

		if (va >= start && va < start + static_size) {
			if (can_addr) {
				*can_addr = (unsigned long) (va - start);
				*can_addr += (unsigned long)
					per_cpu_ptr(base, get_boot_cpu_id());
			}
			return true;
		}
	}
#endif
	/* on UP, can't distinguish from other static vars, always false */
	return false;
}