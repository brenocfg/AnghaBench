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
struct mem_cgroup_per_node {int /*<<< orphan*/  memcg; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 struct mem_cgroup_per_node* mem_cgroup_nodeinfo (struct mem_cgroup*,int) ; 
 struct mem_cgroup* parent_mem_cgroup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mem_cgroup_per_node *
parent_nodeinfo(struct mem_cgroup_per_node *pn, int nid)
{
	struct mem_cgroup *parent;

	parent = parent_mem_cgroup(pn->memcg);
	if (!parent)
		return NULL;
	return mem_cgroup_nodeinfo(parent, nid);
}