#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct o2nm_node {size_t nd_num; int /*<<< orphan*/  nd_item; int /*<<< orphan*/  nd_ip_node; scalar_t__ nd_ipv4_address; } ;
struct o2nm_cluster {scalar_t__ cl_local_node; int /*<<< orphan*/  cl_nodes_lock; int /*<<< orphan*/  cl_nodes_bitmap; struct o2nm_node** cl_nodes; int /*<<< orphan*/  cl_node_ip_tree; scalar_t__ cl_has_local; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_parent; } ;
struct config_group {TYPE_1__ cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_CLUSTER ; 
 scalar_t__ O2NM_INVALID_NODE_NUM ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_disconnect_node (struct o2nm_node*) ; 
 int /*<<< orphan*/  o2net_stop_listening (struct o2nm_node*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct o2nm_cluster* to_o2nm_cluster (int /*<<< orphan*/ ) ; 
 struct o2nm_node* to_o2nm_node (struct config_item*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2nm_node_group_drop_item(struct config_group *group,
				      struct config_item *item)
{
	struct o2nm_node *node = to_o2nm_node(item);
	struct o2nm_cluster *cluster = to_o2nm_cluster(group->cg_item.ci_parent);

	if (cluster->cl_nodes[node->nd_num] == node) {
		o2net_disconnect_node(node);

		if (cluster->cl_has_local &&
		    (cluster->cl_local_node == node->nd_num)) {
			cluster->cl_has_local = 0;
			cluster->cl_local_node = O2NM_INVALID_NODE_NUM;
			o2net_stop_listening(node);
		}
	}

	/* XXX call into net to stop this node from trading messages */

	write_lock(&cluster->cl_nodes_lock);

	/* XXX sloppy */
	if (node->nd_ipv4_address)
		rb_erase(&node->nd_ip_node, &cluster->cl_node_ip_tree);

	/* nd_num might be 0 if the node number hasn't been set.. */
	if (cluster->cl_nodes[node->nd_num] == node) {
		cluster->cl_nodes[node->nd_num] = NULL;
		clear_bit(node->nd_num, cluster->cl_nodes_bitmap);
	}
	write_unlock(&cluster->cl_nodes_lock);

	mlog(ML_CLUSTER, "o2nm: Unregistered node %s\n",
	     config_item_name(&node->nd_item));

	config_item_put(item);
}