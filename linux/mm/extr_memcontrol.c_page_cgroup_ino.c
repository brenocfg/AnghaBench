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
struct page {int /*<<< orphan*/  mem_cgroup; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  cgroup; } ;
struct mem_cgroup {TYPE_1__ css; } ;
typedef  unsigned long ino_t ;

/* Variables and functions */
 int CSS_ONLINE ; 
 scalar_t__ PageSlab (struct page*) ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 struct mem_cgroup* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long cgroup_ino (int /*<<< orphan*/ ) ; 
 struct mem_cgroup* memcg_from_slab_page (struct page*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

ino_t page_cgroup_ino(struct page *page)
{
	struct mem_cgroup *memcg;
	unsigned long ino = 0;

	rcu_read_lock();
	if (PageSlab(page) && !PageTail(page))
		memcg = memcg_from_slab_page(page);
	else
		memcg = READ_ONCE(page->mem_cgroup);
	while (memcg && !(memcg->css.flags & CSS_ONLINE))
		memcg = parent_mem_cgroup(memcg);
	if (memcg)
		ino = cgroup_ino(memcg->css.cgroup);
	rcu_read_unlock();
	return ino;
}