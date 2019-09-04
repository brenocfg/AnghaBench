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
struct hstate {int /*<<< orphan*/  max_huge_pages; scalar_t__* nr_huge_pages_node; scalar_t__ nr_huge_pages; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NODEMASK_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NODEMASK_FREE (int /*<<< orphan*/ *) ; 
 int NUMA_NO_NODE ; 
 size_t N_MEMORY ; 
 int __GFP_NORETRY ; 
 int /*<<< orphan*/  gigantic_page_supported () ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 
 scalar_t__ init_nodemask_of_mempolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_nodemask_of_node (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * node_states ; 
 int /*<<< orphan*/  nodemask_t ; 
 int /*<<< orphan*/ * nodes_allowed ; 
 int /*<<< orphan*/  set_max_huge_pages (struct hstate*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __nr_hugepages_store_common(bool obey_mempolicy,
					   struct hstate *h, int nid,
					   unsigned long count, size_t len)
{
	int err;
	NODEMASK_ALLOC(nodemask_t, nodes_allowed, GFP_KERNEL | __GFP_NORETRY);

	if (hstate_is_gigantic(h) && !gigantic_page_supported()) {
		err = -EINVAL;
		goto out;
	}

	if (nid == NUMA_NO_NODE) {
		/*
		 * global hstate attribute
		 */
		if (!(obey_mempolicy &&
				init_nodemask_of_mempolicy(nodes_allowed))) {
			NODEMASK_FREE(nodes_allowed);
			nodes_allowed = &node_states[N_MEMORY];
		}
	} else if (nodes_allowed) {
		/*
		 * per node hstate attribute: adjust count to global,
		 * but restrict alloc/free to the specified node.
		 */
		count += h->nr_huge_pages - h->nr_huge_pages_node[nid];
		init_nodemask_of_node(nodes_allowed, nid);
	} else
		nodes_allowed = &node_states[N_MEMORY];

	h->max_huge_pages = set_max_huge_pages(h, count, nodes_allowed);

	if (nodes_allowed != &node_states[N_MEMORY])
		NODEMASK_FREE(nodes_allowed);

	return len;
out:
	NODEMASK_FREE(nodes_allowed);
	return err;
}