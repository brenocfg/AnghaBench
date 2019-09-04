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
struct page {int dummy; } ;
struct cmp_pages {int num_pages; struct page** dst_pages; struct page** src_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ memcmp (void*,void*,unsigned int) ; 

__attribute__((used)) static int btrfs_cmp_data(u64 len, struct cmp_pages *cmp)
{
	int ret = 0;
	int i;
	struct page *src_page, *dst_page;
	unsigned int cmp_len = PAGE_SIZE;
	void *addr, *dst_addr;

	i = 0;
	while (len) {
		if (len < PAGE_SIZE)
			cmp_len = len;

		BUG_ON(i >= cmp->num_pages);

		src_page = cmp->src_pages[i];
		dst_page = cmp->dst_pages[i];
		ASSERT(PageLocked(src_page));
		ASSERT(PageLocked(dst_page));

		addr = kmap_atomic(src_page);
		dst_addr = kmap_atomic(dst_page);

		flush_dcache_page(src_page);
		flush_dcache_page(dst_page);

		if (memcmp(addr, dst_addr, cmp_len))
			ret = -EBADE;

		kunmap_atomic(addr);
		kunmap_atomic(dst_addr);

		if (ret)
			break;

		len -= cmp_len;
		i++;
	}

	return ret;
}