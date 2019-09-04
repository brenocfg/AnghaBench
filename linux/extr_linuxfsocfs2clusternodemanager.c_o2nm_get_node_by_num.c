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
typedef  size_t u8 ;
struct o2nm_node {int /*<<< orphan*/  nd_item; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_nodes_lock; struct o2nm_node** cl_nodes; } ;

/* Variables and functions */
 size_t O2NM_MAX_NODES ; 
 int /*<<< orphan*/  config_item_get (int /*<<< orphan*/ *) ; 
 TYPE_1__* o2nm_single_cluster ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct o2nm_node *o2nm_get_node_by_num(u8 node_num)
{
	struct o2nm_node *node = NULL;

	if (node_num >= O2NM_MAX_NODES || o2nm_single_cluster == NULL)
		goto out;

	read_lock(&o2nm_single_cluster->cl_nodes_lock);
	node = o2nm_single_cluster->cl_nodes[node_num];
	if (node)
		config_item_get(&node->nd_item);
	read_unlock(&o2nm_single_cluster->cl_nodes_lock);
out:
	return node;
}