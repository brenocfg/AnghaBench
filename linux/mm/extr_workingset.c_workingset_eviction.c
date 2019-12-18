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
struct pglist_data {int dummy; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {int /*<<< orphan*/  inactive_age; } ;

/* Variables and functions */
 int PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageWorkingset (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 unsigned long atomic_long_inc_return (int /*<<< orphan*/ *) ; 
 int mem_cgroup_id (struct mem_cgroup*) ; 
 struct lruvec* mem_cgroup_lruvec (struct pglist_data*,struct mem_cgroup*) ; 
 void* pack_shadow (int,struct pglist_data*,unsigned long,int /*<<< orphan*/ ) ; 
 int page_count (struct page*) ; 
 struct mem_cgroup* page_memcg (struct page*) ; 
 struct pglist_data* page_pgdat (struct page*) ; 

void *workingset_eviction(struct page *page)
{
	struct pglist_data *pgdat = page_pgdat(page);
	struct mem_cgroup *memcg = page_memcg(page);
	int memcgid = mem_cgroup_id(memcg);
	unsigned long eviction;
	struct lruvec *lruvec;

	/* Page is fully exclusive and pins page->mem_cgroup */
	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON_PAGE(page_count(page), page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	lruvec = mem_cgroup_lruvec(pgdat, memcg);
	eviction = atomic_long_inc_return(&lruvec->inactive_age);
	return pack_shadow(memcgid, pgdat, eviction, PageWorkingset(page));
}