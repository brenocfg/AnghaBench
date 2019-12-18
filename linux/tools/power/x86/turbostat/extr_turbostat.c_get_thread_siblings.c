#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpu_topology {int logical_cpu_id; int physical_core_id; int /*<<< orphan*/  put_ids; int /*<<< orphan*/  thread_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  thread_id; } ;
struct TYPE_3__ {int max_cpu_num; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BITMASK_SIZE ; 
 int /*<<< orphan*/  CPU_ALLOC (int) ; 
 size_t CPU_ALLOC_SIZE (int) ; 
 int CPU_COUNT_S (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_SET_S (int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_ZERO_S (size_t,int /*<<< orphan*/ ) ; 
 TYPE_2__* cpus ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned long*,char*) ; 
 int get_core_id (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 TYPE_1__ topo ; 

int get_thread_siblings(struct cpu_topology *thiscpu)
{
	char path[80], character;
	FILE *filep;
	unsigned long map;
	int so, shift, sib_core;
	int cpu = thiscpu->logical_cpu_id;
	int offset = topo.max_cpu_num + 1;
	size_t size;
	int thread_id = 0;

	thiscpu->put_ids = CPU_ALLOC((topo.max_cpu_num + 1));
	if (thiscpu->thread_id < 0)
		thiscpu->thread_id = thread_id++;
	if (!thiscpu->put_ids)
		return -1;

	size = CPU_ALLOC_SIZE((topo.max_cpu_num + 1));
	CPU_ZERO_S(size, thiscpu->put_ids);

	sprintf(path,
		"/sys/devices/system/cpu/cpu%d/topology/thread_siblings", cpu);
	filep = fopen_or_die(path, "r");
	do {
		offset -= BITMASK_SIZE;
		if (fscanf(filep, "%lx%c", &map, &character) != 2)
			err(1, "%s: failed to parse file", path);
		for (shift = 0; shift < BITMASK_SIZE; shift++) {
			if ((map >> shift) & 0x1) {
				so = shift + offset;
				sib_core = get_core_id(so);
				if (sib_core == thiscpu->physical_core_id) {
					CPU_SET_S(so, size, thiscpu->put_ids);
					if ((so != cpu) &&
					    (cpus[so].thread_id < 0))
						cpus[so].thread_id =
								    thread_id++;
				}
			}
		}
	} while (!strncmp(&character, ",", 1));
	fclose(filep);

	return CPU_COUNT_S(size, thiscpu->put_ids);
}