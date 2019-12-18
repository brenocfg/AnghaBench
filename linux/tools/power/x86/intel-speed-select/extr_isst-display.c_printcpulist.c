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
 int /*<<< orphan*/  CPU_COUNT_S (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET_S (int,int,int /*<<< orphan*/ *) ; 
 int get_topo_max_cpus () ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void printcpulist(int str_len, char *str, int mask_size,
			 cpu_set_t *cpu_mask)
{
	int i, first, curr_index, index;

	if (!CPU_COUNT_S(mask_size, cpu_mask)) {
		snprintf(str, str_len, "none");
		return;
	}

	curr_index = 0;
	first = 1;
	for (i = 0; i < get_topo_max_cpus(); ++i) {
		if (!CPU_ISSET_S(i, mask_size, cpu_mask))
			continue;
		if (!first) {
			index = snprintf(&str[curr_index],
					 str_len - curr_index, ",");
			curr_index += index;
		}
		index = snprintf(&str[curr_index], str_len - curr_index, "%d",
				 i);
		curr_index += index;
		first = 0;
	}
}