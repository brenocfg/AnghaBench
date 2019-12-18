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
struct TYPE_2__ {int punit_cpu_core; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* cpu_map ; 
 int topo_max_cpus ; 

int find_phy_core_num(int logical_cpu)
{
	if (logical_cpu < topo_max_cpus)
		return cpu_map[logical_cpu].punit_cpu_core;

	return -EINVAL;
}