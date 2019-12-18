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
struct page {TYPE_1__* mapping; } ;
struct p9_fid {int dummy; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct bio_vec {scalar_t__ bv_len; struct page* bv_page; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int /*<<< orphan*/ ,struct bio_vec*,int,scalar_t__) ; 
 int p9_client_read (struct p9_fid*,int /*<<< orphan*/ ,struct iov_iter*,int*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int v9fs_readpage_from_fscache (struct inode*,struct page*) ; 
 int /*<<< orphan*/  v9fs_readpage_to_fscache (struct inode*,struct page*) ; 
 int /*<<< orphan*/  v9fs_uncache_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,int,scalar_t__) ; 

__attribute__((used)) static int v9fs_fid_readpage(void *data, struct page *page)
{
	struct p9_fid *fid = data;
	struct inode *inode = page->mapping->host;
	struct bio_vec bvec = {.bv_page = page, .bv_len = PAGE_SIZE};
	struct iov_iter to;
	int retval, err;

	p9_debug(P9_DEBUG_VFS, "\n");

	BUG_ON(!PageLocked(page));

	retval = v9fs_readpage_from_fscache(inode, page);
	if (retval == 0)
		return retval;

	iov_iter_bvec(&to, READ, &bvec, 1, PAGE_SIZE);

	retval = p9_client_read(fid, page_offset(page), &to, &err);
	if (err) {
		v9fs_uncache_page(inode, page);
		retval = err;
		goto done;
	}

	zero_user(page, retval, PAGE_SIZE - retval);
	flush_dcache_page(page);
	SetPageUptodate(page);

	v9fs_readpage_to_fscache(inode, page);
	retval = 0;

done:
	unlock_page(page);
	return retval;
}