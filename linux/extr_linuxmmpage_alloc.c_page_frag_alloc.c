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
struct page_frag_cache {void* va; unsigned int pagecnt_bias; unsigned int offset; int /*<<< orphan*/  pfmemalloc; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 struct page* __page_frag_cache_refill (struct page_frag_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_is_pfmemalloc (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,unsigned int) ; 
 int /*<<< orphan*/  page_ref_sub_and_test (struct page*,unsigned int) ; 
 int /*<<< orphan*/  set_page_count (struct page*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_page (void*) ; 

void *page_frag_alloc(struct page_frag_cache *nc,
		      unsigned int fragsz, gfp_t gfp_mask)
{
	unsigned int size = PAGE_SIZE;
	struct page *page;
	int offset;

	if (unlikely(!nc->va)) {
refill:
		page = __page_frag_cache_refill(nc, gfp_mask);
		if (!page)
			return NULL;

#if (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
		/* if size can vary use size else just use PAGE_SIZE */
		size = nc->size;
#endif
		/* Even if we own the page, we do not use atomic_set().
		 * This would break get_page_unless_zero() users.
		 */
		page_ref_add(page, size);

		/* reset page count bias and offset to start of new frag */
		nc->pfmemalloc = page_is_pfmemalloc(page);
		nc->pagecnt_bias = size + 1;
		nc->offset = size;
	}

	offset = nc->offset - fragsz;
	if (unlikely(offset < 0)) {
		page = virt_to_page(nc->va);

		if (!page_ref_sub_and_test(page, nc->pagecnt_bias))
			goto refill;

#if (PAGE_SIZE < PAGE_FRAG_CACHE_MAX_SIZE)
		/* if size can vary use size else just use PAGE_SIZE */
		size = nc->size;
#endif
		/* OK, page count is 0, we can safely set it */
		set_page_count(page, size + 1);

		/* reset page count bias and offset to start of new frag */
		nc->pagecnt_bias = size + 1;
		offset = size - fragsz;
	}

	nc->pagecnt_bias--;
	nc->offset = offset;

	return nc->va + offset;
}