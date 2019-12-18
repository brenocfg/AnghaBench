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
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  CPU_ISSET_S (int,int,int /*<<< orphan*/ *) ; 
 unsigned int* calloc (int,int) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int get_topo_max_cpus () ; 
 int snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void printcpumask(int str_len, char *str, int mask_size,
			 cpu_set_t *cpu_mask)
{
	int i, max_cpus = get_topo_max_cpus();
	unsigned int *mask;
	int size, index, curr_index;

	size = max_cpus / (sizeof(unsigned int) * 8);
	if (max_cpus % (sizeof(unsigned int) * 8))
		size++;

	mask = calloc(size, sizeof(unsigned int));
	if (!mask)
		return;

	for (i = 0; i < max_cpus; ++i) {
		int mask_index, bit_index;

		if (!CPU_ISSET_S(i, mask_size, cpu_mask))
			continue;

		mask_index = i / (sizeof(unsigned int) * 8);
		bit_index = i % (sizeof(unsigned int) * 8);
		mask[mask_index] |= BIT(bit_index);
	}

	curr_index = 0;
	for (i = size - 1; i >= 0; --i) {
		index = snprintf(&str[curr_index], str_len - curr_index, "%08x",
				 mask[i]);
		curr_index += index;
		if (i) {
			strncat(&str[curr_index], ",", str_len - curr_index);
			curr_index++;
		}
	}

	free(mask);
}