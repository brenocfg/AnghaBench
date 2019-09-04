#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ci_parent; } ;
struct o2nm_node {TYPE_2__ nd_item; } ;
struct o2nm_cluster {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ci_parent; } ;

/* Variables and functions */
 struct o2nm_cluster* to_o2nm_cluster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct o2nm_cluster *to_o2nm_cluster_from_node(struct o2nm_node *node)
{
	/* through the first node_set .parent
	 * mycluster/nodes/mynode == o2nm_cluster->o2nm_node_group->o2nm_node */
	if (node->nd_item.ci_parent)
		return to_o2nm_cluster(node->nd_item.ci_parent->ci_parent);
	else
		return NULL;
}