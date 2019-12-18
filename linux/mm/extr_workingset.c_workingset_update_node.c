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
struct xa_node {scalar_t__ count; scalar_t__ nr_values; int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WORKINGSET_NODES ; 
 int /*<<< orphan*/  __dec_lruvec_slab_state (struct xa_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_lruvec_slab_state (struct xa_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shadow_nodes ; 

void workingset_update_node(struct xa_node *node)
{
	/*
	 * Track non-empty nodes that contain only shadow entries;
	 * unlink those that contain pages or are being freed.
	 *
	 * Avoid acquiring the list_lru lock when the nodes are
	 * already where they should be. The list_empty() test is safe
	 * as node->private_list is protected by the i_pages lock.
	 */
	VM_WARN_ON_ONCE(!irqs_disabled());  /* For __inc_lruvec_page_state */

	if (node->count && node->count == node->nr_values) {
		if (list_empty(&node->private_list)) {
			list_lru_add(&shadow_nodes, &node->private_list);
			__inc_lruvec_slab_state(node, WORKINGSET_NODES);
		}
	} else {
		if (!list_empty(&node->private_list)) {
			list_lru_del(&shadow_nodes, &node->private_list);
			__dec_lruvec_slab_state(node, WORKINGSET_NODES);
		}
	}
}