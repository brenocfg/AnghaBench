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
struct rmap_walk_control {void* arg; int /*<<< orphan*/  anon_lock; int /*<<< orphan*/  done; int /*<<< orphan*/  rmap_one; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageCompound (struct page*) ; 
 scalar_t__ PageDoubleMap (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ TTU_MUNLOCK ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  page_lock_anon_vma_read ; 
 int /*<<< orphan*/  page_not_mapped ; 
 int /*<<< orphan*/  rmap_walk (struct page*,struct rmap_walk_control*) ; 
 int /*<<< orphan*/  try_to_unmap_one ; 

void try_to_munlock(struct page *page)
{
	struct rmap_walk_control rwc = {
		.rmap_one = try_to_unmap_one,
		.arg = (void *)TTU_MUNLOCK,
		.done = page_not_mapped,
		.anon_lock = page_lock_anon_vma_read,

	};

	VM_BUG_ON_PAGE(!PageLocked(page) || PageLRU(page), page);
	VM_BUG_ON_PAGE(PageCompound(page) && PageDoubleMap(page), page);

	rmap_walk(page, &rwc);
}