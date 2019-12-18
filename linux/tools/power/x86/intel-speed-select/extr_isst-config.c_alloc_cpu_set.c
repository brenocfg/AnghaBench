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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CPU_ALLOC (scalar_t__) ; 
 size_t CPU_ALLOC_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  CPU_ZERO_S (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ topo_max_cpus ; 

size_t alloc_cpu_set(cpu_set_t **cpu_set)
{
	cpu_set_t *_cpu_set;
	size_t size;

	_cpu_set = CPU_ALLOC((topo_max_cpus + 1));
	if (_cpu_set == NULL)
		err(3, "CPU_ALLOC");
	size = CPU_ALLOC_SIZE((topo_max_cpus + 1));
	CPU_ZERO_S(size, _cpu_set);

	*cpu_set = _cpu_set;
	return size;
}