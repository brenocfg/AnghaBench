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
struct file {int dummy; } ;
struct address_space {TYPE_1__* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGECACHE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*,int /*<<< orphan*/ ,unsigned int,long long) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int nfs_flush_incompatible (struct file*,struct page*) ; 
 int nfs_readpage (struct file*,struct page*) ; 
 scalar_t__ nfs_want_read_modify_write (struct file*,struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int nfs_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata)
{
	int ret;
	pgoff_t index = pos >> PAGE_SHIFT;
	struct page *page;
	int once_thru = 0;

	dfprintk(PAGECACHE, "NFS: write_begin(%pD2(%lu), %u@%lld)\n",
		file, mapping->host->i_ino, len, (long long) pos);

start:
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
	*pagep = page;

	ret = nfs_flush_incompatible(file, page);
	if (ret) {
		unlock_page(page);
		put_page(page);
	} else if (!once_thru &&
		   nfs_want_read_modify_write(file, page, pos, len)) {
		once_thru = 1;
		ret = nfs_readpage(file, page);
		put_page(page);
		if (!ret)
			goto start;
	}
	return ret;
}