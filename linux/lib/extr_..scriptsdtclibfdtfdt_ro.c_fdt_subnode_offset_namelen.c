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
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  FDT_RO_PROBE (void const*) ; 
 int fdt_next_node (void const*,int,int*) ; 
 scalar_t__ fdt_nodename_eq_ (void const*,int,char const*,int) ; 

int fdt_subnode_offset_namelen(const void *fdt, int offset,
			       const char *name, int namelen)
{
	int depth;

	FDT_RO_PROBE(fdt);

	for (depth = 0;
	     (offset >= 0) && (depth >= 0);
	     offset = fdt_next_node(fdt, offset, &depth))
		if ((depth == 1)
		    && fdt_nodename_eq_(fdt, offset, name, namelen))
			return offset;

	if (depth < 0)
		return -FDT_ERR_NOTFOUND;
	return offset; /* error */
}