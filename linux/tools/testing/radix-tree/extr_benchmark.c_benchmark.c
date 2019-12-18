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
 int /*<<< orphan*/  RADIX_TREE_MAP_SHIFT ; 
 int /*<<< orphan*/  benchmark_size (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  printv (int,char*,...) ; 

void benchmark(void)
{
	unsigned long size[] = {1 << 10, 1 << 20, 0};
	unsigned long step[] = {1, 2, 7, 15, 63, 64, 65,
				128, 256, 512, 12345, 0};
	int c, s;

	printv(1, "starting benchmarks\n");
	printv(1, "RADIX_TREE_MAP_SHIFT = %d\n", RADIX_TREE_MAP_SHIFT);

	for (c = 0; size[c]; c++)
		for (s = 0; step[s]; s++)
			benchmark_size(size[c], step[s]);
}