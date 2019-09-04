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
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 int fdt_node_end_offset_ (void*,int) ; 
 int /*<<< orphan*/  fdt_offset_ptr_w_ (void*,int) ; 
 int fdt_splice_struct_ (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int fdt_del_node(void *fdt, int nodeoffset)
{
	int endoffset;

	FDT_RW_CHECK_HEADER(fdt);

	endoffset = fdt_node_end_offset_(fdt, nodeoffset);
	if (endoffset < 0)
		return endoffset;

	return fdt_splice_struct_(fdt, fdt_offset_ptr_w_(fdt, nodeoffset),
				  endoffset - nodeoffset, 0);
}