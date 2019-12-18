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
struct TYPE_3__ {scalar_t__ mpage; } ;
struct z_erofs_decompress_frontend {int headoffset; TYPE_1__ map; int /*<<< orphan*/  clt; } ;
struct page {scalar_t__ index; TYPE_2__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
typedef  int erofs_off_t ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 struct z_erofs_decompress_frontend DECOMPRESS_FRONTEND_INIT (struct inode* const) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pagepool ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 
 int /*<<< orphan*/  put_pages_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_erofs_readpage (struct page*,int) ; 
 int /*<<< orphan*/  z_erofs_collector_end (int /*<<< orphan*/ *) ; 
 int z_erofs_do_read_page (struct z_erofs_decompress_frontend*,struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z_erofs_submit_and_unzip (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int z_erofs_vle_normalaccess_readpage(struct file *file,
					     struct page *page)
{
	struct inode *const inode = page->mapping->host;
	struct z_erofs_decompress_frontend f = DECOMPRESS_FRONTEND_INIT(inode);
	int err;
	LIST_HEAD(pagepool);

	trace_erofs_readpage(page, false);

	f.headoffset = (erofs_off_t)page->index << PAGE_SHIFT;

	err = z_erofs_do_read_page(&f, page, &pagepool);
	(void)z_erofs_collector_end(&f.clt);

	/* if some compressed cluster ready, need submit them anyway */
	z_erofs_submit_and_unzip(inode->i_sb, &f.clt, &pagepool, true);

	if (err)
		erofs_err(inode->i_sb, "failed to read, err [%d]", err);

	if (f.map.mpage)
		put_page(f.map.mpage);

	/* clean up the remaining free pages */
	put_pages_list(&pagepool);
	return err;
}