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
struct page {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_VM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  NR_FILE_THPS ; 
 int /*<<< orphan*/  NR_SHMEM ; 
 int /*<<< orphan*/  NR_SHMEM_THPS ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageMappedToDisk (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  TAINT_BAD_PAGE ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  account_page_cleaned (struct page*,struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleancache_invalidate_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  cleancache_put_page (struct page*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dump_page (struct page*,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  filemap_nr_thps_dec (struct address_space*) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  inode_to_wb (int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_exiting (struct address_space*) ; 
 int page_count (struct page*) ; 
 int page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_mapcount_reset (struct page*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  page_ref_sub (struct page*,int) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unaccount_page_cache_page(struct address_space *mapping,
				      struct page *page)
{
	int nr;

	/*
	 * if we're uptodate, flush out into the cleancache, otherwise
	 * invalidate any existing cleancache entries.  We can't leave
	 * stale data around in the cleancache once our page is gone
	 */
	if (PageUptodate(page) && PageMappedToDisk(page))
		cleancache_put_page(page);
	else
		cleancache_invalidate_page(mapping, page);

	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(page_mapped(page), page);
	if (!IS_ENABLED(CONFIG_DEBUG_VM) && unlikely(page_mapped(page))) {
		int mapcount;

		pr_alert("BUG: Bad page cache in process %s  pfn:%05lx\n",
			 current->comm, page_to_pfn(page));
		dump_page(page, "still mapped when deleted");
		dump_stack();
		add_taint(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);

		mapcount = page_mapcount(page);
		if (mapping_exiting(mapping) &&
		    page_count(page) >= mapcount + 2) {
			/*
			 * All vmas have already been torn down, so it's
			 * a good bet that actually the page is unmapped,
			 * and we'd prefer not to leak it: if we're wrong,
			 * some other bad page check should catch it later.
			 */
			page_mapcount_reset(page);
			page_ref_sub(page, mapcount);
		}
	}

	/* hugetlb pages do not participate in page cache accounting. */
	if (PageHuge(page))
		return;

	nr = hpage_nr_pages(page);

	__mod_node_page_state(page_pgdat(page), NR_FILE_PAGES, -nr);
	if (PageSwapBacked(page)) {
		__mod_node_page_state(page_pgdat(page), NR_SHMEM, -nr);
		if (PageTransHuge(page))
			__dec_node_page_state(page, NR_SHMEM_THPS);
	} else if (PageTransHuge(page)) {
		__dec_node_page_state(page, NR_FILE_THPS);
		filemap_nr_thps_dec(mapping);
	}

	/*
	 * At this point page must be either written or cleaned by
	 * truncate.  Dirty page here signals a bug and loss of
	 * unwritten data.
	 *
	 * This fixes dirty accounting after removing the page entirely
	 * but leaves PageDirty set: it has no effect for truncated
	 * page and anyway will be cleared before returning page into
	 * buddy allocator.
	 */
	if (WARN_ON_ONCE(PageDirty(page)))
		account_page_cleaned(page, mapping, inode_to_wb(mapping->host));
}