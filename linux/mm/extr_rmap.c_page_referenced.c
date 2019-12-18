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
struct rmap_walk_control {void* arg; int /*<<< orphan*/  invalid_vma; int /*<<< orphan*/  anon_lock; int /*<<< orphan*/  rmap_one; } ;
struct page_referenced_arg {unsigned long vm_flags; int referenced; int /*<<< orphan*/  mapcount; struct mem_cgroup* memcg; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 scalar_t__ PageKsm (struct page*) ; 
 int /*<<< orphan*/  invalid_page_referenced_vma ; 
 int /*<<< orphan*/  page_lock_anon_vma_read ; 
 int /*<<< orphan*/  page_referenced_one ; 
 int /*<<< orphan*/  page_rmapping (struct page*) ; 
 int /*<<< orphan*/  rmap_walk (struct page*,struct rmap_walk_control*) ; 
 int /*<<< orphan*/  total_mapcount (struct page*) ; 
 int trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int page_referenced(struct page *page,
		    int is_locked,
		    struct mem_cgroup *memcg,
		    unsigned long *vm_flags)
{
	int we_locked = 0;
	struct page_referenced_arg pra = {
		.mapcount = total_mapcount(page),
		.memcg = memcg,
	};
	struct rmap_walk_control rwc = {
		.rmap_one = page_referenced_one,
		.arg = (void *)&pra,
		.anon_lock = page_lock_anon_vma_read,
	};

	*vm_flags = 0;
	if (!pra.mapcount)
		return 0;

	if (!page_rmapping(page))
		return 0;

	if (!is_locked && (!PageAnon(page) || PageKsm(page))) {
		we_locked = trylock_page(page);
		if (!we_locked)
			return 1;
	}

	/*
	 * If we are reclaiming on behalf of a cgroup, skip
	 * counting on behalf of references from different
	 * cgroups
	 */
	if (memcg) {
		rwc.invalid_vma = invalid_page_referenced_vma;
	}

	rmap_walk(page, &rwc);
	*vm_flags = pra.vm_flags;

	if (we_locked)
		unlock_page(page);

	return pra.referenced;
}