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
struct TYPE_2__ {long max; long* data; } ;

/* Variables and functions */
 int MAX_CPU ; 
 int MAX_ENTRIES ; 
 int /*<<< orphan*/  bpf_map_lookup_elem (int,long*,long*) ; 
 TYPE_1__* cpu_hist ; 

__attribute__((used)) static void get_data(int fd)
{
	long key, value;
	int c, i;

	for (i = 0; i < MAX_CPU; i++)
		cpu_hist[i].max = 0;

	for (c = 0; c < MAX_CPU; c++) {
		for (i = 0; i < MAX_ENTRIES; i++) {
			key = c * MAX_ENTRIES + i;
			bpf_map_lookup_elem(fd, &key, &value);

			cpu_hist[c].data[i] = value;
			if (value > cpu_hist[c].max)
				cpu_hist[c].max = value;
		}
	}
}