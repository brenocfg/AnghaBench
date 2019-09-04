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
struct page_collect {scalar_t__ nr_pages; unsigned long length; unsigned int expected_pages; int pg_first; struct page** pages; } ;
struct page {int index; } ;
struct ore_io_state {scalar_t__ nr_pages; unsigned long length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,int,unsigned int,unsigned int,int,unsigned long) ; 
 int PAGE_SIZE ; 
 int pcol_try_alloc (struct page_collect*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _maybe_not_all_in_one_io(struct ore_io_state *ios,
	struct page_collect *pcol_src, struct page_collect *pcol)
{
	/* length was wrong or offset was not page aligned */
	BUG_ON(pcol_src->nr_pages < ios->nr_pages);

	if (pcol_src->nr_pages > ios->nr_pages) {
		struct page **src_page;
		unsigned pages_less = pcol_src->nr_pages - ios->nr_pages;
		unsigned long len_less = pcol_src->length - ios->length;
		unsigned i;
		int ret;

		/* This IO was trimmed */
		pcol_src->nr_pages = ios->nr_pages;
		pcol_src->length = ios->length;

		/* Left over pages are passed to the next io */
		pcol->expected_pages += pages_less;
		pcol->nr_pages = pages_less;
		pcol->length = len_less;
		src_page = pcol_src->pages + pcol_src->nr_pages;
		pcol->pg_first = (*src_page)->index;

		ret = pcol_try_alloc(pcol);
		if (unlikely(ret))
			return ret;

		for (i = 0; i < pages_less; ++i)
			pcol->pages[i] = *src_page++;

		EXOFS_DBGMSG("Length was adjusted nr_pages=0x%x "
			"pages_less=0x%x expected_pages=0x%x "
			"next_offset=0x%llx next_len=0x%lx\n",
			pcol_src->nr_pages, pages_less, pcol->expected_pages,
			pcol->pg_first * PAGE_SIZE, pcol->length);
	}
	return 0;
}