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
 int fdt_next_node (void*,int,int*) ; 

int fdt_node_end_offset_(void *fdt, int offset)
{
	int depth = 0;

	while ((offset >= 0) && (depth >= 0))
		offset = fdt_next_node(fdt, offset, &depth);

	return offset;
}