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
typedef  int u64 ;
struct page {int flags; } ;

/* Variables and functions */
 int KPF_ACTIVE ; 
 int KPF_ANON ; 
 int KPF_ARCH ; 
 int KPF_BUDDY ; 
 int KPF_COMPOUND_HEAD ; 
 int KPF_COMPOUND_TAIL ; 
 int KPF_DIRTY ; 
 int KPF_ERROR ; 
 int KPF_HUGE ; 
 int KPF_HWPOISON ; 
 int KPF_IDLE ; 
 int KPF_KSM ; 
 int KPF_LOCKED ; 
 int KPF_LRU ; 
 int KPF_MAPPEDTODISK ; 
 int KPF_MLOCKED ; 
 int KPF_MMAP ; 
 int KPF_NOPAGE ; 
 int KPF_OFFLINE ; 
 int KPF_OWNER_PRIVATE ; 
 int KPF_PGTABLE ; 
 int KPF_PRIVATE ; 
 int KPF_PRIVATE_2 ; 
 int KPF_RECLAIM ; 
 int KPF_REFERENCED ; 
 int KPF_RESERVED ; 
 int KPF_SLAB ; 
 int KPF_SWAPBACKED ; 
 int KPF_SWAPCACHE ; 
 int KPF_THP ; 
 int KPF_UNCACHED ; 
 int KPF_UNEVICTABLE ; 
 int KPF_UPTODATE ; 
 int KPF_WRITEBACK ; 
 int KPF_ZERO_PAGE ; 
 int /*<<< orphan*/  PG_active ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  PG_dirty ; 
 int /*<<< orphan*/  PG_error ; 
 int /*<<< orphan*/  PG_hwpoison ; 
 int /*<<< orphan*/  PG_locked ; 
 int /*<<< orphan*/  PG_lru ; 
 int /*<<< orphan*/  PG_mappedtodisk ; 
 int /*<<< orphan*/  PG_mlocked ; 
 int /*<<< orphan*/  PG_owner_priv_1 ; 
 int /*<<< orphan*/  PG_private ; 
 int /*<<< orphan*/  PG_private_2 ; 
 int /*<<< orphan*/  PG_reclaim ; 
 int /*<<< orphan*/  PG_referenced ; 
 int /*<<< orphan*/  PG_reserved ; 
 int /*<<< orphan*/  PG_slab ; 
 int /*<<< orphan*/  PG_swapbacked ; 
 int /*<<< orphan*/  PG_uncached ; 
 int /*<<< orphan*/  PG_unevictable ; 
 int /*<<< orphan*/  PG_uptodate ; 
 int /*<<< orphan*/  PG_writeback ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageBuddy (struct page*) ; 
 scalar_t__ PageHead (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageKsm (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 scalar_t__ PageOffline (struct page*) ; 
 scalar_t__ PageSlab (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ PageTable (struct page*) ; 
 scalar_t__ PageTail (struct page*) ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 scalar_t__ is_free_buddy_page (struct page*) ; 
 scalar_t__ is_huge_zero_page (struct page*) ; 
 scalar_t__ is_zero_pfn (int /*<<< orphan*/ ) ; 
 int kpf_copy_bit (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ page_count (struct page*) ; 
 scalar_t__ page_is_idle (struct page*) ; 
 scalar_t__ page_mapped (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

u64 stable_page_flags(struct page *page)
{
	u64 k;
	u64 u;

	/*
	 * pseudo flag: KPF_NOPAGE
	 * it differentiates a memory hole from a page with no flags
	 */
	if (!page)
		return 1 << KPF_NOPAGE;

	k = page->flags;
	u = 0;

	/*
	 * pseudo flags for the well known (anonymous) memory mapped pages
	 *
	 * Note that page->_mapcount is overloaded in SLOB/SLUB/SLQB, so the
	 * simple test in page_mapped() is not enough.
	 */
	if (!PageSlab(page) && page_mapped(page))
		u |= 1 << KPF_MMAP;
	if (PageAnon(page))
		u |= 1 << KPF_ANON;
	if (PageKsm(page))
		u |= 1 << KPF_KSM;

	/*
	 * compound pages: export both head/tail info
	 * they together define a compound page's start/end pos and order
	 */
	if (PageHead(page))
		u |= 1 << KPF_COMPOUND_HEAD;
	if (PageTail(page))
		u |= 1 << KPF_COMPOUND_TAIL;
	if (PageHuge(page))
		u |= 1 << KPF_HUGE;
	/*
	 * PageTransCompound can be true for non-huge compound pages (slab
	 * pages or pages allocated by drivers with __GFP_COMP) because it
	 * just checks PG_head/PG_tail, so we need to check PageLRU/PageAnon
	 * to make sure a given page is a thp, not a non-huge compound page.
	 */
	else if (PageTransCompound(page)) {
		struct page *head = compound_head(page);

		if (PageLRU(head) || PageAnon(head))
			u |= 1 << KPF_THP;
		else if (is_huge_zero_page(head)) {
			u |= 1 << KPF_ZERO_PAGE;
			u |= 1 << KPF_THP;
		}
	} else if (is_zero_pfn(page_to_pfn(page)))
		u |= 1 << KPF_ZERO_PAGE;


	/*
	 * Caveats on high order pages: page->_refcount will only be set
	 * -1 on the head page; SLUB/SLQB do the same for PG_slab;
	 * SLOB won't set PG_slab at all on compound pages.
	 */
	if (PageBuddy(page))
		u |= 1 << KPF_BUDDY;
	else if (page_count(page) == 0 && is_free_buddy_page(page))
		u |= 1 << KPF_BUDDY;

	if (PageOffline(page))
		u |= 1 << KPF_OFFLINE;
	if (PageTable(page))
		u |= 1 << KPF_PGTABLE;

	if (page_is_idle(page))
		u |= 1 << KPF_IDLE;

	u |= kpf_copy_bit(k, KPF_LOCKED,	PG_locked);

	u |= kpf_copy_bit(k, KPF_SLAB,		PG_slab);
	if (PageTail(page) && PageSlab(compound_head(page)))
		u |= 1 << KPF_SLAB;

	u |= kpf_copy_bit(k, KPF_ERROR,		PG_error);
	u |= kpf_copy_bit(k, KPF_DIRTY,		PG_dirty);
	u |= kpf_copy_bit(k, KPF_UPTODATE,	PG_uptodate);
	u |= kpf_copy_bit(k, KPF_WRITEBACK,	PG_writeback);

	u |= kpf_copy_bit(k, KPF_LRU,		PG_lru);
	u |= kpf_copy_bit(k, KPF_REFERENCED,	PG_referenced);
	u |= kpf_copy_bit(k, KPF_ACTIVE,	PG_active);
	u |= kpf_copy_bit(k, KPF_RECLAIM,	PG_reclaim);

	if (PageSwapCache(page))
		u |= 1 << KPF_SWAPCACHE;
	u |= kpf_copy_bit(k, KPF_SWAPBACKED,	PG_swapbacked);

	u |= kpf_copy_bit(k, KPF_UNEVICTABLE,	PG_unevictable);
	u |= kpf_copy_bit(k, KPF_MLOCKED,	PG_mlocked);

#ifdef CONFIG_MEMORY_FAILURE
	u |= kpf_copy_bit(k, KPF_HWPOISON,	PG_hwpoison);
#endif

#ifdef CONFIG_ARCH_USES_PG_UNCACHED
	u |= kpf_copy_bit(k, KPF_UNCACHED,	PG_uncached);
#endif

	u |= kpf_copy_bit(k, KPF_RESERVED,	PG_reserved);
	u |= kpf_copy_bit(k, KPF_MAPPEDTODISK,	PG_mappedtodisk);
	u |= kpf_copy_bit(k, KPF_PRIVATE,	PG_private);
	u |= kpf_copy_bit(k, KPF_PRIVATE_2,	PG_private_2);
	u |= kpf_copy_bit(k, KPF_OWNER_PRIVATE,	PG_owner_priv_1);
	u |= kpf_copy_bit(k, KPF_ARCH,		PG_arch_1);

	return u;
}