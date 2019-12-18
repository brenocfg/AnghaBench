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
 int FDT_ERR_INTERNAL ; 
 int fdt_supernode_atdepth_offset (void const*,int,int /*<<< orphan*/ ,int*) ; 

int fdt_node_depth(const void *fdt, int nodeoffset)
{
	int nodedepth;
	int err;

	err = fdt_supernode_atdepth_offset(fdt, nodeoffset, 0, &nodedepth);
	if (err)
		return (err < 0) ? err : -FDT_ERR_INTERNAL;
	return nodedepth;
}