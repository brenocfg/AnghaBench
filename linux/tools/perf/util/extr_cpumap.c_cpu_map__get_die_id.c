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
 int cpu__get_topology_int (int,char*,int*) ; 

int cpu_map__get_die_id(int cpu)
{
	int value, ret = cpu__get_topology_int(cpu, "die_id", &value);

	return ret ?: value;
}