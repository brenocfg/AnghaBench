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

void tcc_memstats(void)
{
#ifdef MEM_DEBUG
	printf ("memory: %d byte(s), max = %d byte(s)\n", mem_cur_size, mem_max_size);
#endif
}