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
struct mem_cgroup_tree_per_node {int dummy; } ;
struct TYPE_2__ {struct mem_cgroup_tree_per_node** rb_tree_per_node; } ;

/* Variables and functions */
 TYPE_1__ soft_limit_tree ; 

__attribute__((used)) static struct mem_cgroup_tree_per_node *
soft_limit_tree_node(int nid)
{
	return soft_limit_tree.rb_tree_per_node[nid];
}