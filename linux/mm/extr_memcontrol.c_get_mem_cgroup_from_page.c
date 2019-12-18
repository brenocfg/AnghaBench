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
struct mem_cgroup {int /*<<< orphan*/  css; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_tryget_online (int /*<<< orphan*/ *) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mem_cgroup* root_mem_cgroup ; 

struct mem_cgroup *get_mem_cgroup_from_page(struct page *page)
{
	struct mem_cgroup *memcg = page->mem_cgroup;

	if (mem_cgroup_disabled())
		return NULL;

	rcu_read_lock();
	if (!memcg || !css_tryget_online(&memcg->css))
		memcg = root_mem_cgroup;
	rcu_read_unlock();
	return memcg;
}