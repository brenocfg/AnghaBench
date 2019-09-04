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
struct radix_tree_node {scalar_t__ count; scalar_t__ exceptional; int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shadow_nodes ; 

void workingset_update_node(struct radix_tree_node *node)
{
	/*
	 * Track non-empty nodes that contain only shadow entries;
	 * unlink those that contain pages or are being freed.
	 *
	 * Avoid acquiring the list_lru lock when the nodes are
	 * already where they should be. The list_empty() test is safe
	 * as node->private_list is protected by the i_pages lock.
	 */
	if (node->count && node->count == node->exceptional) {
		if (list_empty(&node->private_list))
			list_lru_add(&shadow_nodes, &node->private_list);
	} else {
		if (!list_empty(&node->private_list))
			list_lru_del(&shadow_nodes, &node->private_list);
	}
}