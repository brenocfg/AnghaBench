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
struct TYPE_2__ {int num_cpus; int max_cpu_num; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,...) ; 
 char getc (int /*<<< orphan*/ *) ; 
 int* irq_column_2_cpu ; 
 int* irqs_per_cpu ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 TYPE_1__ topo ; 
 int /*<<< orphan*/  warn (char*,int,int) ; 

int snapshot_proc_interrupts(void)
{
	static FILE *fp;
	int column, retval;

	if (fp == NULL)
		fp = fopen_or_die("/proc/interrupts", "r");
	else
		rewind(fp);

	/* read 1st line of /proc/interrupts to get cpu* name for each column */
	for (column = 0; column < topo.num_cpus; ++column) {
		int cpu_number;

		retval = fscanf(fp, " CPU%d", &cpu_number);
		if (retval != 1)
			break;

		if (cpu_number > topo.max_cpu_num) {
			warn("/proc/interrupts: cpu%d: > %d", cpu_number, topo.max_cpu_num);
			return 1;
		}

		irq_column_2_cpu[column] = cpu_number;
		irqs_per_cpu[cpu_number] = 0;
	}

	/* read /proc/interrupt count lines and sum up irqs per cpu */
	while (1) {
		int column;
		char buf[64];

		retval = fscanf(fp, " %s:", buf);	/* flush irq# "N:" */
		if (retval != 1)
			break;

		/* read the count per cpu */
		for (column = 0; column < topo.num_cpus; ++column) {

			int cpu_number, irq_count;

			retval = fscanf(fp, " %d", &irq_count);
			if (retval != 1)
				break;

			cpu_number = irq_column_2_cpu[column];
			irqs_per_cpu[cpu_number] += irq_count;

		}

		while (getc(fp) != '\n')
			;	/* flush interrupt description */

	}
	return 0;
}