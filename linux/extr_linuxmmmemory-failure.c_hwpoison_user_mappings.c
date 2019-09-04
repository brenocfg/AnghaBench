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
struct address_space {int dummy; } ;
typedef  enum ttu_flags { ____Placeholder_ttu_flags } ttu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int MF_ACTION_REQUIRED ; 
 int MF_MUST_KILL ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageKsm (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int PageMlocked (struct page*) ; 
 scalar_t__ PageReserved (struct page*) ; 
 scalar_t__ PageSlab (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int TTU_IGNORE_ACCESS ; 
 int TTU_IGNORE_HWPOISON ; 
 int TTU_IGNORE_MLOCK ; 
 int /*<<< orphan*/  collect_procs (struct page*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kill_procs (int /*<<< orphan*/ *,int,int,unsigned long,int) ; 
 scalar_t__ mapping_cap_writeback_dirty (struct address_space*) ; 
 int /*<<< orphan*/  page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ page_mkclean (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,...) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  shake_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tokill ; 
 int try_to_unmap (struct page*,int) ; 

__attribute__((used)) static bool hwpoison_user_mappings(struct page *p, unsigned long pfn,
				  int flags, struct page **hpagep)
{
	enum ttu_flags ttu = TTU_IGNORE_MLOCK | TTU_IGNORE_ACCESS;
	struct address_space *mapping;
	LIST_HEAD(tokill);
	bool unmap_success;
	int kill = 1, forcekill;
	struct page *hpage = *hpagep;
	bool mlocked = PageMlocked(hpage);

	/*
	 * Here we are interested only in user-mapped pages, so skip any
	 * other types of pages.
	 */
	if (PageReserved(p) || PageSlab(p))
		return true;
	if (!(PageLRU(hpage) || PageHuge(p)))
		return true;

	/*
	 * This check implies we don't kill processes if their pages
	 * are in the swap cache early. Those are always late kills.
	 */
	if (!page_mapped(hpage))
		return true;

	if (PageKsm(p)) {
		pr_err("Memory failure: %#lx: can't handle KSM pages.\n", pfn);
		return false;
	}

	if (PageSwapCache(p)) {
		pr_err("Memory failure: %#lx: keeping poisoned page in swap cache\n",
			pfn);
		ttu |= TTU_IGNORE_HWPOISON;
	}

	/*
	 * Propagate the dirty bit from PTEs to struct page first, because we
	 * need this to decide if we should kill or just drop the page.
	 * XXX: the dirty test could be racy: set_page_dirty() may not always
	 * be called inside page lock (it's recommended but not enforced).
	 */
	mapping = page_mapping(hpage);
	if (!(flags & MF_MUST_KILL) && !PageDirty(hpage) && mapping &&
	    mapping_cap_writeback_dirty(mapping)) {
		if (page_mkclean(hpage)) {
			SetPageDirty(hpage);
		} else {
			kill = 0;
			ttu |= TTU_IGNORE_HWPOISON;
			pr_info("Memory failure: %#lx: corrupted page was clean: dropped without side effects\n",
				pfn);
		}
	}

	/*
	 * First collect all the processes that have the page
	 * mapped in dirty form.  This has to be done before try_to_unmap,
	 * because ttu takes the rmap data structures down.
	 *
	 * Error handling: We ignore errors here because
	 * there's nothing that can be done.
	 */
	if (kill)
		collect_procs(hpage, &tokill, flags & MF_ACTION_REQUIRED);

	unmap_success = try_to_unmap(hpage, ttu);
	if (!unmap_success)
		pr_err("Memory failure: %#lx: failed to unmap page (mapcount=%d)\n",
		       pfn, page_mapcount(hpage));

	/*
	 * try_to_unmap() might put mlocked page in lru cache, so call
	 * shake_page() again to ensure that it's flushed.
	 */
	if (mlocked)
		shake_page(hpage, 0);

	/*
	 * Now that the dirty bit has been propagated to the
	 * struct page and all unmaps done we can decide if
	 * killing is needed or not.  Only kill when the page
	 * was dirty or the process is not restartable,
	 * otherwise the tokill list is merely
	 * freed.  When there was a problem unmapping earlier
	 * use a more force-full uncatchable kill to prevent
	 * any accesses to the poisoned memory.
	 */
	forcekill = PageDirty(hpage) || (flags & MF_MUST_KILL);
	kill_procs(&tokill, forcekill, !unmap_success, pfn, flags);

	return unmap_success;
}