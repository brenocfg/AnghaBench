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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF_KOBJ ; 
 int EINVAL ; 
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int fdt_next_node (void const*,int,int*) ; 
 int /*<<< orphan*/  of_fdt_device_is_available (void const*,int) ; 
 int /*<<< orphan*/  populate_node (void const*,int,void**,struct device_node*,struct device_node**,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  reverse_nodes (struct device_node*) ; 

__attribute__((used)) static int unflatten_dt_nodes(const void *blob,
			      void *mem,
			      struct device_node *dad,
			      struct device_node **nodepp)
{
	struct device_node *root;
	int offset = 0, depth = 0, initial_depth = 0;
#define FDT_MAX_DEPTH	64
	struct device_node *nps[FDT_MAX_DEPTH];
	void *base = mem;
	bool dryrun = !base;

	if (nodepp)
		*nodepp = NULL;

	/*
	 * We're unflattening device sub-tree if @dad is valid. There are
	 * possibly multiple nodes in the first level of depth. We need
	 * set @depth to 1 to make fdt_next_node() happy as it bails
	 * immediately when negative @depth is found. Otherwise, the device
	 * nodes except the first one won't be unflattened successfully.
	 */
	if (dad)
		depth = initial_depth = 1;

	root = dad;
	nps[depth] = dad;

	for (offset = 0;
	     offset >= 0 && depth >= initial_depth;
	     offset = fdt_next_node(blob, offset, &depth)) {
		if (WARN_ON_ONCE(depth >= FDT_MAX_DEPTH))
			continue;

		if (!IS_ENABLED(CONFIG_OF_KOBJ) &&
		    !of_fdt_device_is_available(blob, offset))
			continue;

		if (!populate_node(blob, offset, &mem, nps[depth],
				   &nps[depth+1], dryrun))
			return mem - base;

		if (!dryrun && nodepp && !*nodepp)
			*nodepp = nps[depth+1];
		if (!dryrun && !root)
			root = nps[depth+1];
	}

	if (offset < 0 && offset != -FDT_ERR_NOTFOUND) {
		pr_err("Error %d processing FDT\n", offset);
		return -EINVAL;
	}

	/*
	 * Reverse the child list. Some drivers assumes node order matches .dts
	 * node order
	 */
	if (!dryrun)
		reverse_nodes(root);

	return mem - base;
}