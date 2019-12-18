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
struct zone {int dummy; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_flags; } ;
struct pagevec {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int FOLL_DUMP ; 
 int FOLL_GET ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PageMlocked (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 scalar_t__ PageTransTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  VM_LOCKED_CLEAR_MASK ; 
 int /*<<< orphan*/  __munlock_pagevec (struct pagevec*,struct zone*) ; 
 unsigned long __munlock_pagevec_fill (struct pagevec*,struct vm_area_struct*,struct zone*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* follow_page (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 unsigned int munlock_vma_page (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void munlock_vma_pages_range(struct vm_area_struct *vma,
			     unsigned long start, unsigned long end)
{
	vma->vm_flags &= VM_LOCKED_CLEAR_MASK;

	while (start < end) {
		struct page *page;
		unsigned int page_mask = 0;
		unsigned long page_increm;
		struct pagevec pvec;
		struct zone *zone;

		pagevec_init(&pvec);
		/*
		 * Although FOLL_DUMP is intended for get_dump_page(),
		 * it just so happens that its special treatment of the
		 * ZERO_PAGE (returning an error instead of doing get_page)
		 * suits munlock very well (and if somehow an abnormal page
		 * has sneaked into the range, we won't oops here: great).
		 */
		page = follow_page(vma, start, FOLL_GET | FOLL_DUMP);

		if (page && !IS_ERR(page)) {
			if (PageTransTail(page)) {
				VM_BUG_ON_PAGE(PageMlocked(page), page);
				put_page(page); /* follow_page_mask() */
			} else if (PageTransHuge(page)) {
				lock_page(page);
				/*
				 * Any THP page found by follow_page_mask() may
				 * have gotten split before reaching
				 * munlock_vma_page(), so we need to compute
				 * the page_mask here instead.
				 */
				page_mask = munlock_vma_page(page);
				unlock_page(page);
				put_page(page); /* follow_page_mask() */
			} else {
				/*
				 * Non-huge pages are handled in batches via
				 * pagevec. The pin from follow_page_mask()
				 * prevents them from collapsing by THP.
				 */
				pagevec_add(&pvec, page);
				zone = page_zone(page);

				/*
				 * Try to fill the rest of pagevec using fast
				 * pte walk. This will also update start to
				 * the next page to process. Then munlock the
				 * pagevec.
				 */
				start = __munlock_pagevec_fill(&pvec, vma,
						zone, start, end);
				__munlock_pagevec(&pvec, zone);
				goto next;
			}
		}
		page_increm = 1 + page_mask;
		start += page_increm * PAGE_SIZE;
next:
		cond_resched();
	}
}