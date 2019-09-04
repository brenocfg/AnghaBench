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
struct cpu_topology {int logical_cpu_id; } ;
struct TYPE_2__ {int max_cpu_num; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 TYPE_1__ topo ; 

int get_physical_node_id(struct cpu_topology *thiscpu)
{
	char path[80];
	FILE *filep;
	int i;
	int cpu = thiscpu->logical_cpu_id;

	for (i = 0; i <= topo.max_cpu_num; i++) {
		sprintf(path, "/sys/devices/system/cpu/cpu%d/node%i/cpulist",
			cpu, i);
		filep = fopen(path, "r");
		if (!filep)
			continue;
		fclose(filep);
		return i;
	}
	return -1;
}