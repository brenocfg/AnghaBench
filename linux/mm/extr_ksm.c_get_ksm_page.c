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
struct stable_node {int /*<<< orphan*/  kpfn; } ;
struct page {int /*<<< orphan*/  mapping; } ;
typedef  enum get_ksm_page_flags { ____Placeholder_get_ksm_page_flags } get_ksm_page_flags ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GET_KSM_PAGE_LOCK ; 
 int GET_KSM_PAGE_NOLOCK ; 
 int GET_KSM_PAGE_TRYLOCK ; 
 unsigned long PAGE_MAPPING_KSM ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  get_page_unless_zero (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remove_node_from_stable_tree (struct stable_node*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static struct page *get_ksm_page(struct stable_node *stable_node,
				 enum get_ksm_page_flags flags)
{
	struct page *page;
	void *expected_mapping;
	unsigned long kpfn;

	expected_mapping = (void *)((unsigned long)stable_node |
					PAGE_MAPPING_KSM);
again:
	kpfn = READ_ONCE(stable_node->kpfn); /* Address dependency. */
	page = pfn_to_page(kpfn);
	if (READ_ONCE(page->mapping) != expected_mapping)
		goto stale;

	/*
	 * We cannot do anything with the page while its refcount is 0.
	 * Usually 0 means free, or tail of a higher-order page: in which
	 * case this node is no longer referenced, and should be freed;
	 * however, it might mean that the page is under page_ref_freeze().
	 * The __remove_mapping() case is easy, again the node is now stale;
	 * the same is in reuse_ksm_page() case; but if page is swapcache
	 * in migrate_page_move_mapping(), it might still be our page,
	 * in which case it's essential to keep the node.
	 */
	while (!get_page_unless_zero(page)) {
		/*
		 * Another check for page->mapping != expected_mapping would
		 * work here too.  We have chosen the !PageSwapCache test to
		 * optimize the common case, when the page is or is about to
		 * be freed: PageSwapCache is cleared (under spin_lock_irq)
		 * in the ref_freeze section of __remove_mapping(); but Anon
		 * page->mapping reset to NULL later, in free_pages_prepare().
		 */
		if (!PageSwapCache(page))
			goto stale;
		cpu_relax();
	}

	if (READ_ONCE(page->mapping) != expected_mapping) {
		put_page(page);
		goto stale;
	}

	if (flags == GET_KSM_PAGE_TRYLOCK) {
		if (!trylock_page(page)) {
			put_page(page);
			return ERR_PTR(-EBUSY);
		}
	} else if (flags == GET_KSM_PAGE_LOCK)
		lock_page(page);

	if (flags != GET_KSM_PAGE_NOLOCK) {
		if (READ_ONCE(page->mapping) != expected_mapping) {
			unlock_page(page);
			put_page(page);
			goto stale;
		}
	}
	return page;

stale:
	/*
	 * We come here from above when page->mapping or !PageSwapCache
	 * suggests that the node is stale; but it might be under migration.
	 * We need smp_rmb(), matching the smp_wmb() in ksm_migrate_page(),
	 * before checking whether node->kpfn has been changed.
	 */
	smp_rmb();
	if (READ_ONCE(stable_node->kpfn) != kpfn)
		goto again;
	remove_node_from_stable_tree(stable_node);
	return NULL;
}