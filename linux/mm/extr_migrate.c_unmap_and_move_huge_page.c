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
struct anon_vma {int dummy; } ;
typedef  struct page* (* new_page_t ) (struct page*,unsigned long) ;
typedef  int /*<<< orphan*/  (* free_page_t ) (struct page*,unsigned long) ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int MIGRATEPAGE_SUCCESS ; 
#define  MIGRATE_SYNC 129 
#define  MIGRATE_SYNC_NO_COPY 128 
 scalar_t__ PageAnon (struct page*) ; 
 int TTU_IGNORE_ACCESS ; 
 int TTU_IGNORE_MLOCK ; 
 int TTU_MIGRATION ; 
 int /*<<< orphan*/  hugepage_migration_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  move_hugetlb_state (struct page*,struct page*,int) ; 
 int move_to_new_page (struct page*,struct page*,int) ; 
 struct anon_vma* page_get_anon_vma (struct page*) ; 
 int /*<<< orphan*/  page_hstate (struct page*) ; 
 scalar_t__ page_mapped (struct page*) ; 
 int /*<<< orphan*/  page_mapping (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  put_anon_vma (struct anon_vma*) ; 
 int /*<<< orphan*/  putback_active_hugepage (struct page*) ; 
 int /*<<< orphan*/  remove_migration_ptes (struct page*,struct page*,int) ; 
 int /*<<< orphan*/  try_to_unmap (struct page*,int) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int unmap_and_move_huge_page(new_page_t get_new_page,
				free_page_t put_new_page, unsigned long private,
				struct page *hpage, int force,
				enum migrate_mode mode, int reason)
{
	int rc = -EAGAIN;
	int page_was_mapped = 0;
	struct page *new_hpage;
	struct anon_vma *anon_vma = NULL;

	/*
	 * Migratability of hugepages depends on architectures and their size.
	 * This check is necessary because some callers of hugepage migration
	 * like soft offline and memory hotremove don't walk through page
	 * tables or check whether the hugepage is pmd-based or not before
	 * kicking migration.
	 */
	if (!hugepage_migration_supported(page_hstate(hpage))) {
		putback_active_hugepage(hpage);
		return -ENOSYS;
	}

	new_hpage = get_new_page(hpage, private);
	if (!new_hpage)
		return -ENOMEM;

	if (!trylock_page(hpage)) {
		if (!force)
			goto out;
		switch (mode) {
		case MIGRATE_SYNC:
		case MIGRATE_SYNC_NO_COPY:
			break;
		default:
			goto out;
		}
		lock_page(hpage);
	}

	/*
	 * Check for pages which are in the process of being freed.  Without
	 * page_mapping() set, hugetlbfs specific move page routine will not
	 * be called and we could leak usage counts for subpools.
	 */
	if (page_private(hpage) && !page_mapping(hpage)) {
		rc = -EBUSY;
		goto out_unlock;
	}

	if (PageAnon(hpage))
		anon_vma = page_get_anon_vma(hpage);

	if (unlikely(!trylock_page(new_hpage)))
		goto put_anon;

	if (page_mapped(hpage)) {
		try_to_unmap(hpage,
			TTU_MIGRATION|TTU_IGNORE_MLOCK|TTU_IGNORE_ACCESS);
		page_was_mapped = 1;
	}

	if (!page_mapped(hpage))
		rc = move_to_new_page(new_hpage, hpage, mode);

	if (page_was_mapped)
		remove_migration_ptes(hpage,
			rc == MIGRATEPAGE_SUCCESS ? new_hpage : hpage, false);

	unlock_page(new_hpage);

put_anon:
	if (anon_vma)
		put_anon_vma(anon_vma);

	if (rc == MIGRATEPAGE_SUCCESS) {
		move_hugetlb_state(hpage, new_hpage, reason);
		put_new_page = NULL;
	}

out_unlock:
	unlock_page(hpage);
out:
	if (rc != -EAGAIN)
		putback_active_hugepage(hpage);

	/*
	 * If migration was not successful and there's a freeing callback, use
	 * it.  Otherwise, put_page() will drop the reference grabbed during
	 * isolation.
	 */
	if (put_new_page)
		put_new_page(new_hpage, private);
	else
		putback_active_hugepage(new_hpage);

	return rc;
}