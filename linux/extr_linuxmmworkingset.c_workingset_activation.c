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
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {int /*<<< orphan*/  inactive_age; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_cgroup_disabled () ; 
 struct lruvec* mem_cgroup_lruvec (int /*<<< orphan*/ ,struct mem_cgroup*) ; 
 struct mem_cgroup* page_memcg_rcu (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void workingset_activation(struct page *page)
{
	struct mem_cgroup *memcg;
	struct lruvec *lruvec;

	rcu_read_lock();
	/*
	 * Filter non-memcg pages here, e.g. unmap can call
	 * mark_page_accessed() on VDSO pages.
	 *
	 * XXX: See workingset_refault() - this should return
	 * root_mem_cgroup even for !CONFIG_MEMCG.
	 */
	memcg = page_memcg_rcu(page);
	if (!mem_cgroup_disabled() && !memcg)
		goto out;
	lruvec = mem_cgroup_lruvec(page_pgdat(page), memcg);
	atomic_long_inc(&lruvec->inactive_age);
out:
	rcu_read_unlock();
}