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
struct hstate {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int EINVAL ; 
 int NUMA_NO_NODE ; 
 size_t N_MEMORY ; 
 int /*<<< orphan*/  gigantic_page_runtime_supported () ; 
 scalar_t__ hstate_is_gigantic (struct hstate*) ; 
 scalar_t__ init_nodemask_of_mempolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_nodemask_of_node (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * node_states ; 
 int set_max_huge_pages (struct hstate*,unsigned long,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __nr_hugepages_store_common(bool obey_mempolicy,
					   struct hstate *h, int nid,
					   unsigned long count, size_t len)
{
	int err;
	nodemask_t nodes_allowed, *n_mask;

	if (hstate_is_gigantic(h) && !gigantic_page_runtime_supported())
		return -EINVAL;

	if (nid == NUMA_NO_NODE) {
		/*
		 * global hstate attribute
		 */
		if (!(obey_mempolicy &&
				init_nodemask_of_mempolicy(&nodes_allowed)))
			n_mask = &node_states[N_MEMORY];
		else
			n_mask = &nodes_allowed;
	} else {
		/*
		 * Node specific request.  count adjustment happens in
		 * set_max_huge_pages() after acquiring hugetlb_lock.
		 */
		init_nodemask_of_node(&nodes_allowed, nid);
		n_mask = &nodes_allowed;
	}

	err = set_max_huge_pages(h, count, nid, n_mask);

	return err ? err : len;
}