#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct orangefs_writepages {int npages; size_t off; size_t len; TYPE_1__** pages; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; TYPE_7__* bv; } ;
struct orangefs_write_range {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  size_t loff_t ;
struct TYPE_14__ {scalar_t__ bv_offset; scalar_t__ bv_len; TYPE_1__* bv_page; } ;
struct TYPE_13__ {struct inode* host; } ;
struct TYPE_12__ {TYPE_6__* mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (TYPE_1__*) ; 
 int /*<<< orphan*/  ORANGEFS_IO_WRITE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PagePrivate (TYPE_1__*) ; 
 int /*<<< orphan*/  SetPageError (TYPE_1__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  end_page_writeback (TYPE_1__*) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int /*<<< orphan*/ ,TYPE_7__*,int,size_t) ; 
 int /*<<< orphan*/  kfree (struct orangefs_write_range*) ; 
 int /*<<< orphan*/  mapping_set_error (TYPE_6__*,scalar_t__) ; 
 scalar_t__ max (size_t,scalar_t__) ; 
 scalar_t__ min (scalar_t__,size_t) ; 
 scalar_t__ page_offset (TYPE_1__*) ; 
 scalar_t__ page_private (TYPE_1__*) ; 
 int /*<<< orphan*/  put_page (TYPE_1__*) ; 
 int /*<<< orphan*/  set_page_writeback (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_page (TYPE_1__*) ; 
 scalar_t__ wait_for_direct_io (int /*<<< orphan*/ ,struct inode*,size_t*,struct iov_iter*,size_t,int /*<<< orphan*/ ,struct orangefs_write_range*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orangefs_writepages_work(struct orangefs_writepages *ow,
    struct writeback_control *wbc)
{
	struct inode *inode = ow->pages[0]->mapping->host;
	struct orangefs_write_range *wrp, wr;
	struct iov_iter iter;
	ssize_t ret;
	size_t len;
	loff_t off;
	int i;

	len = i_size_read(inode);

	for (i = 0; i < ow->npages; i++) {
		set_page_writeback(ow->pages[i]);
		ow->bv[i].bv_page = ow->pages[i];
		ow->bv[i].bv_len = min(page_offset(ow->pages[i]) + PAGE_SIZE,
		    ow->off + ow->len) -
		    max(ow->off, page_offset(ow->pages[i]));
		if (i == 0)
			ow->bv[i].bv_offset = ow->off -
			    page_offset(ow->pages[i]);
		else
			ow->bv[i].bv_offset = 0;
	}
	iov_iter_bvec(&iter, WRITE, ow->bv, ow->npages, ow->len);

	WARN_ON(ow->off >= len);
	if (ow->off + ow->len > len)
		ow->len = len - ow->off;

	off = ow->off;
	wr.uid = ow->uid;
	wr.gid = ow->gid;
	ret = wait_for_direct_io(ORANGEFS_IO_WRITE, inode, &off, &iter, ow->len,
	    0, &wr, NULL);
	if (ret < 0) {
		for (i = 0; i < ow->npages; i++) {
			SetPageError(ow->pages[i]);
			mapping_set_error(ow->pages[i]->mapping, ret);
			if (PagePrivate(ow->pages[i])) {
				wrp = (struct orangefs_write_range *)
				    page_private(ow->pages[i]);
				ClearPagePrivate(ow->pages[i]);
				put_page(ow->pages[i]);
				kfree(wrp);
			}
			end_page_writeback(ow->pages[i]);
			unlock_page(ow->pages[i]);
		}
	} else {
		ret = 0;
		for (i = 0; i < ow->npages; i++) {
			if (PagePrivate(ow->pages[i])) {
				wrp = (struct orangefs_write_range *)
				    page_private(ow->pages[i]);
				ClearPagePrivate(ow->pages[i]);
				put_page(ow->pages[i]);
				kfree(wrp);
			}
			end_page_writeback(ow->pages[i]);
			unlock_page(ow->pages[i]);
		}
	}
	return ret;
}