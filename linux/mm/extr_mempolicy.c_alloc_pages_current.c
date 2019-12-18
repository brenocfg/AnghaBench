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
struct page {int dummy; } ;
struct mempolicy {scalar_t__ mode; } ;
typedef  int gfp_t ;

/* Variables and functions */
 scalar_t__ MPOL_INTERLEAVE ; 
 int __GFP_THISNODE ; 
 struct page* __alloc_pages_nodemask (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* alloc_page_interleave (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct mempolicy default_policy ; 
 struct mempolicy* get_task_policy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  interleave_nodes (struct mempolicy*) ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int /*<<< orphan*/  policy_node (int,struct mempolicy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_nodemask (int,struct mempolicy*) ; 

struct page *alloc_pages_current(gfp_t gfp, unsigned order)
{
	struct mempolicy *pol = &default_policy;
	struct page *page;

	if (!in_interrupt() && !(gfp & __GFP_THISNODE))
		pol = get_task_policy(current);

	/*
	 * No reference counting needed for current->mempolicy
	 * nor system default_policy
	 */
	if (pol->mode == MPOL_INTERLEAVE)
		page = alloc_page_interleave(gfp, order, interleave_nodes(pol));
	else
		page = __alloc_pages_nodemask(gfp, order,
				policy_node(gfp, pol, numa_node_id()),
				policy_nodemask(gfp, pol));

	return page;
}