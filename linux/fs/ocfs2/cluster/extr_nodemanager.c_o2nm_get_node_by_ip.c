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
struct o2nm_node {int /*<<< orphan*/  nd_item; } ;
struct o2nm_cluster {int /*<<< orphan*/  cl_nodes_lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_get (int /*<<< orphan*/ *) ; 
 struct o2nm_node* o2nm_node_ip_tree_lookup (struct o2nm_cluster*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct o2nm_cluster* o2nm_single_cluster ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct o2nm_node *o2nm_get_node_by_ip(__be32 addr)
{
	struct o2nm_node *node = NULL;
	struct o2nm_cluster *cluster = o2nm_single_cluster;

	if (cluster == NULL)
		goto out;

	read_lock(&cluster->cl_nodes_lock);
	node = o2nm_node_ip_tree_lookup(cluster, addr, NULL, NULL);
	if (node)
		config_item_get(&node->nd_item);
	read_unlock(&cluster->cl_nodes_lock);

out:
	return node;
}