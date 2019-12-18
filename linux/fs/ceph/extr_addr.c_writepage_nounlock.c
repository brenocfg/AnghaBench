#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int /*<<< orphan*/  pages_skipped; } ;
struct page {scalar_t__ private; int /*<<< orphan*/  index; TYPE_2__* mapping; } ;
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_mtime; } ;
struct ceph_writeback_ctl {int /*<<< orphan*/  truncate_size; int /*<<< orphan*/  truncate_seq; int /*<<< orphan*/  i_size; } ;
struct ceph_snap_context {scalar_t__ seq; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_layout; } ;
struct ceph_fs_client {int blacklisted; TYPE_4__* mount_options; int /*<<< orphan*/  writeback_count; TYPE_3__* client; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  congestion_kb; } ;
struct TYPE_8__ {int /*<<< orphan*/  osdc; } ;
struct TYPE_7__ {TYPE_1__* a_ops; struct inode* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* invalidatepage ) (struct page*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 scalar_t__ CONGESTION_OFF_THRESH (int /*<<< orphan*/ ) ; 
 scalar_t__ CONGESTION_ON_THRESH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EBLACKLISTED ; 
 int ERESTARTSYS ; 
 int PAGE_SIZE ; 
 int PF_MEMALLOC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_long_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_long_inc_return (int /*<<< orphan*/ *) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int ceph_osdc_writepages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ceph_snap_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct page**,int) ; 
 int /*<<< orphan*/  ceph_put_snap_context (struct ceph_snap_context*) ; 
 int /*<<< orphan*/  ceph_put_wrbuffer_cap_refs (struct ceph_inode_info*,int,struct ceph_snap_context*) ; 
 int /*<<< orphan*/  ceph_vino (struct inode*) ; 
 int /*<<< orphan*/  clear_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 struct ceph_snap_context* get_oldest_context (struct inode*,struct ceph_writeback_ctl*,struct ceph_snap_context*) ; 
 int /*<<< orphan*/  inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 
 struct ceph_snap_context* page_snap_context (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct page*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int writepage_nounlock(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode;
	struct ceph_inode_info *ci;
	struct ceph_fs_client *fsc;
	struct ceph_snap_context *snapc, *oldest;
	loff_t page_off = page_offset(page);
	int err, len = PAGE_SIZE;
	struct ceph_writeback_ctl ceph_wbc;

	dout("writepage %p idx %lu\n", page, page->index);

	inode = page->mapping->host;
	ci = ceph_inode(inode);
	fsc = ceph_inode_to_client(inode);

	/* verify this is a writeable snap context */
	snapc = page_snap_context(page);
	if (!snapc) {
		dout("writepage %p page %p not dirty?\n", inode, page);
		return 0;
	}
	oldest = get_oldest_context(inode, &ceph_wbc, snapc);
	if (snapc->seq > oldest->seq) {
		dout("writepage %p page %p snapc %p not writeable - noop\n",
		     inode, page, snapc);
		/* we should only noop if called by kswapd */
		WARN_ON(!(current->flags & PF_MEMALLOC));
		ceph_put_snap_context(oldest);
		redirty_page_for_writepage(wbc, page);
		return 0;
	}
	ceph_put_snap_context(oldest);

	/* is this a partial page at end of file? */
	if (page_off >= ceph_wbc.i_size) {
		dout("%p page eof %llu\n", page, ceph_wbc.i_size);
		page->mapping->a_ops->invalidatepage(page, 0, PAGE_SIZE);
		return 0;
	}

	if (ceph_wbc.i_size < page_off + len)
		len = ceph_wbc.i_size - page_off;

	dout("writepage %p page %p index %lu on %llu~%u snapc %p seq %lld\n",
	     inode, page, page->index, page_off, len, snapc, snapc->seq);

	if (atomic_long_inc_return(&fsc->writeback_count) >
	    CONGESTION_ON_THRESH(fsc->mount_options->congestion_kb))
		set_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);

	set_page_writeback(page);
	err = ceph_osdc_writepages(&fsc->client->osdc, ceph_vino(inode),
				   &ci->i_layout, snapc, page_off, len,
				   ceph_wbc.truncate_seq,
				   ceph_wbc.truncate_size,
				   &inode->i_mtime, &page, 1);
	if (err < 0) {
		struct writeback_control tmp_wbc;
		if (!wbc)
			wbc = &tmp_wbc;
		if (err == -ERESTARTSYS) {
			/* killed by SIGKILL */
			dout("writepage interrupted page %p\n", page);
			redirty_page_for_writepage(wbc, page);
			end_page_writeback(page);
			return err;
		}
		if (err == -EBLACKLISTED)
			fsc->blacklisted = true;
		dout("writepage setting page/mapping error %d %p\n",
		     err, page);
		mapping_set_error(&inode->i_data, err);
		wbc->pages_skipped++;
	} else {
		dout("writepage cleaned page %p\n", page);
		err = 0;  /* vfs expects us to return 0 */
	}
	page->private = 0;
	ClearPagePrivate(page);
	end_page_writeback(page);
	ceph_put_wrbuffer_cap_refs(ci, 1, snapc);
	ceph_put_snap_context(snapc);  /* page's reference */

	if (atomic_long_dec_return(&fsc->writeback_count) <
	    CONGESTION_OFF_THRESH(fsc->mount_options->congestion_kb))
		clear_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);

	return err;
}