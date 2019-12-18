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
struct page {int /*<<< orphan*/  index; int /*<<< orphan*/  lru; int /*<<< orphan*/  flags; } ;
struct mpage_readpage_args {int is_readahead; unsigned int nr_pages; scalar_t__ bio; struct page* page; int /*<<< orphan*/  get_block; } ;
struct list_head {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  get_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_RAHEAD ; 
 int /*<<< orphan*/  add_to_page_cache_lru (struct page*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ do_mpage_readpage (struct mpage_readpage_args*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 struct page* lru_to_page (struct list_head*) ; 
 int /*<<< orphan*/  mpage_bio_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  readahead_gfp_mask (struct address_space*) ; 

int
mpage_readpages(struct address_space *mapping, struct list_head *pages,
				unsigned nr_pages, get_block_t get_block)
{
	struct mpage_readpage_args args = {
		.get_block = get_block,
		.is_readahead = true,
	};
	unsigned page_idx;

	for (page_idx = 0; page_idx < nr_pages; page_idx++) {
		struct page *page = lru_to_page(pages);

		prefetchw(&page->flags);
		list_del(&page->lru);
		if (!add_to_page_cache_lru(page, mapping,
					page->index,
					readahead_gfp_mask(mapping))) {
			args.page = page;
			args.nr_pages = nr_pages - page_idx;
			args.bio = do_mpage_readpage(&args);
		}
		put_page(page);
	}
	BUG_ON(!list_empty(pages));
	if (args.bio)
		mpage_bio_submit(REQ_OP_READ, REQ_RAHEAD, args.bio);
	return 0;
}