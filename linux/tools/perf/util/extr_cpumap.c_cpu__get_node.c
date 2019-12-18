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
 int* cpunode_map ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int cpu__get_node(int cpu)
{
	if (unlikely(cpunode_map == NULL)) {
		pr_debug("cpu_map not initialized\n");
		return -1;
	}

	return cpunode_map[cpu];
}