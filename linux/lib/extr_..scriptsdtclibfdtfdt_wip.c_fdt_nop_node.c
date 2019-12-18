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
 int fdt_node_end_offset_ (void*,int) ; 
 int /*<<< orphan*/  fdt_nop_region_ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdt_offset_ptr_w (void*,int,int /*<<< orphan*/ ) ; 

int fdt_nop_node(void *fdt, int nodeoffset)
{
	int endoffset;

	endoffset = fdt_node_end_offset_(fdt, nodeoffset);
	if (endoffset < 0)
		return endoffset;

	fdt_nop_region_(fdt_offset_ptr_w(fdt, nodeoffset, 0),
			endoffset - nodeoffset);
	return 0;
}