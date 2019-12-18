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
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct orangefs_write_range {size_t pos; size_t len; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct bio_vec {size_t bv_len; size_t bv_offset; struct page* bv_page; } ;
typedef  scalar_t__ ssize_t ;
typedef  size_t loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  ORANGEFS_IO_WRITE ; 
 size_t PAGE_SIZE ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int /*<<< orphan*/ ,struct bio_vec*,int,size_t) ; 
 int /*<<< orphan*/  kfree (struct orangefs_write_range*) ; 
 int /*<<< orphan*/  mapping_set_error (TYPE_1__*,scalar_t__) ; 
 size_t page_offset (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 scalar_t__ wait_for_direct_io (int /*<<< orphan*/ ,struct inode*,size_t*,struct iov_iter*,size_t,size_t,struct orangefs_write_range*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orangefs_writepage_locked(struct page *page,
    struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct orangefs_write_range *wr = NULL;
	struct iov_iter iter;
	struct bio_vec bv;
	size_t len, wlen;
	ssize_t ret;
	loff_t off;

	set_page_writeback(page);

	len = i_size_read(inode);
	if (PagePrivate(page)) {
		wr = (struct orangefs_write_range *)page_private(page);
		WARN_ON(wr->pos >= len);
		off = wr->pos;
		if (off + wr->len > len)
			wlen = len - off;
		else
			wlen = wr->len;
	} else {
		WARN_ON(1);
		off = page_offset(page);
		if (off + PAGE_SIZE > len)
			wlen = len - off;
		else
			wlen = PAGE_SIZE;
	}
	/* Should've been handled in orangefs_invalidatepage. */
	WARN_ON(off == len || off + wlen > len);

	bv.bv_page = page;
	bv.bv_len = wlen;
	bv.bv_offset = off % PAGE_SIZE;
	WARN_ON(wlen == 0);
	iov_iter_bvec(&iter, WRITE, &bv, 1, wlen);

	ret = wait_for_direct_io(ORANGEFS_IO_WRITE, inode, &off, &iter, wlen,
	    len, wr, NULL);
	if (ret < 0) {
		SetPageError(page);
		mapping_set_error(page->mapping, ret);
	} else {
		ret = 0;
	}
	if (wr) {
		kfree(wr);
		set_page_private(page, 0);
		ClearPagePrivate(page);
		put_page(page);
	}
	return ret;
}