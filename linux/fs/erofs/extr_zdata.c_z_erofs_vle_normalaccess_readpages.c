#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct page* mpage; } ;
struct z_erofs_decompress_frontend {int headoffset; TYPE_1__ map; int /*<<< orphan*/  clt; } ;
struct page {scalar_t__ index; int /*<<< orphan*/  lru; int /*<<< orphan*/  flags; } ;
struct list_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct erofs_sb_info {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int erofs_off_t ;
struct TYPE_4__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 struct z_erofs_decompress_frontend DECOMPRESS_FRONTEND_INIT (struct inode* const) ; 
 TYPE_2__* EROFS_I (struct inode* const) ; 
 struct erofs_sb_info* EROFS_I_SB (struct inode* const) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PageReadahead (struct page*) ; 
 scalar_t__ add_to_page_cache_lru (struct page*,struct address_space*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct page* lru_to_page (struct list_head*) ; 
 int /*<<< orphan*/  mapping_gfp_constraint (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  pagepool ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  put_pages_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int should_decompress_synchronously (struct erofs_sb_info* const,unsigned int) ; 
 int /*<<< orphan*/  trace_erofs_readpages (struct inode*,struct page*,unsigned int,int) ; 
 int /*<<< orphan*/  z_erofs_collector_end (int /*<<< orphan*/ *) ; 
 int z_erofs_do_read_page (struct z_erofs_decompress_frontend*,struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z_erofs_submit_and_unzip (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int z_erofs_vle_normalaccess_readpages(struct file *filp,
					      struct address_space *mapping,
					      struct list_head *pages,
					      unsigned int nr_pages)
{
	struct inode *const inode = mapping->host;
	struct erofs_sb_info *const sbi = EROFS_I_SB(inode);

	bool sync = should_decompress_synchronously(sbi, nr_pages);
	struct z_erofs_decompress_frontend f = DECOMPRESS_FRONTEND_INIT(inode);
	gfp_t gfp = mapping_gfp_constraint(mapping, GFP_KERNEL);
	struct page *head = NULL;
	LIST_HEAD(pagepool);

	trace_erofs_readpages(mapping->host, lru_to_page(pages),
			      nr_pages, false);

	f.headoffset = (erofs_off_t)lru_to_page(pages)->index << PAGE_SHIFT;

	for (; nr_pages; --nr_pages) {
		struct page *page = lru_to_page(pages);

		prefetchw(&page->flags);
		list_del(&page->lru);

		/*
		 * A pure asynchronous readahead is indicated if
		 * a PG_readahead marked page is hitted at first.
		 * Let's also do asynchronous decompression for this case.
		 */
		sync &= !(PageReadahead(page) && !head);

		if (add_to_page_cache_lru(page, mapping, page->index, gfp)) {
			list_add(&page->lru, &pagepool);
			continue;
		}

		set_page_private(page, (unsigned long)head);
		head = page;
	}

	while (head) {
		struct page *page = head;
		int err;

		/* traversal in reverse order */
		head = (void *)page_private(page);

		err = z_erofs_do_read_page(&f, page, &pagepool);
		if (err)
			erofs_err(inode->i_sb,
				  "readahead error at page %lu @ nid %llu",
				  page->index, EROFS_I(inode)->nid);
		put_page(page);
	}

	(void)z_erofs_collector_end(&f.clt);

	z_erofs_submit_and_unzip(inode->i_sb, &f.clt, &pagepool, sync);

	if (f.map.mpage)
		put_page(f.map.mpage);

	/* clean up the remaining free pages */
	put_pages_list(&pagepool);
	return 0;
}