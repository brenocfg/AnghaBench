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
struct bitmask {unsigned int size; } ;

/* Variables and functions */
 struct bitmask* numa_allocate_cpumask () ; 
 scalar_t__ numa_bitmask_isbitset (struct bitmask*,unsigned int) ; 
 int /*<<< orphan*/  numa_node_to_cpus (int,struct bitmask*) ; 

__attribute__((used)) static bool node_has_cpus(int node)
{
	struct bitmask *cpu = numa_allocate_cpumask();
	unsigned int i;

	if (cpu && !numa_node_to_cpus(node, cpu)) {
		for (i = 0; i < cpu->size; i++) {
			if (numa_bitmask_isbitset(cpu, i))
				return true;
		}
	}

	return false; /* lets fall back to nocpus safely */
}