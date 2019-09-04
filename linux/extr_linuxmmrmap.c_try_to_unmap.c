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
struct rmap_walk_control {void* arg; int /*<<< orphan*/  invalid_vma; int /*<<< orphan*/  anon_lock; int /*<<< orphan*/  done; int /*<<< orphan*/  rmap_one; } ;
struct page {int dummy; } ;
typedef  enum ttu_flags { ____Placeholder_ttu_flags } ttu_flags ;

/* Variables and functions */
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int TTU_MIGRATION ; 
 int TTU_RMAP_LOCKED ; 
 int TTU_SPLIT_FREEZE ; 
 int /*<<< orphan*/  invalid_migration_vma ; 
 int /*<<< orphan*/  page_lock_anon_vma_read ; 
 int /*<<< orphan*/  page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_mapcount_is_zero ; 
 int /*<<< orphan*/  rmap_walk (struct page*,struct rmap_walk_control*) ; 
 int /*<<< orphan*/  rmap_walk_locked (struct page*,struct rmap_walk_control*) ; 
 int /*<<< orphan*/  try_to_unmap_one ; 

bool try_to_unmap(struct page *page, enum ttu_flags flags)
{
	struct rmap_walk_control rwc = {
		.rmap_one = try_to_unmap_one,
		.arg = (void *)flags,
		.done = page_mapcount_is_zero,
		.anon_lock = page_lock_anon_vma_read,
	};

	/*
	 * During exec, a temporary VMA is setup and later moved.
	 * The VMA is moved under the anon_vma lock but not the
	 * page tables leading to a race where migration cannot
	 * find the migration ptes. Rather than increasing the
	 * locking requirements of exec(), migration skips
	 * temporary VMAs until after exec() completes.
	 */
	if ((flags & (TTU_MIGRATION|TTU_SPLIT_FREEZE))
	    && !PageKsm(page) && PageAnon(page))
		rwc.invalid_vma = invalid_migration_vma;

	if (flags & TTU_RMAP_LOCKED)
		rmap_walk_locked(page, &rwc);
	else
		rmap_walk(page, &rwc);

	return !page_mapcount(page) ? true : false;
}