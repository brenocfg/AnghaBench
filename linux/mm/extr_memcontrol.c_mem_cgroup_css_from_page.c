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
struct page {struct mem_cgroup* mem_cgroup; } ;
struct cgroup_subsys_state {int dummy; } ;
struct mem_cgroup {struct cgroup_subsys_state css; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_cgrp_subsys ; 
 struct mem_cgroup* root_mem_cgroup ; 

struct cgroup_subsys_state *mem_cgroup_css_from_page(struct page *page)
{
	struct mem_cgroup *memcg;

	memcg = page->mem_cgroup;

	if (!memcg || !cgroup_subsys_on_dfl(memory_cgrp_subsys))
		memcg = root_mem_cgroup;

	return &memcg->css;
}