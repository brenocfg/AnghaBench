#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct page {scalar_t__ private; } ;
struct inode {int /*<<< orphan*/  i_sb; struct address_space* i_mapping; } ;
struct ceph_snap_context {int dummy; } ;
struct ceph_osd_request {int r_result; int r_num_ops; TYPE_1__* r_ops; struct ceph_snap_context* r_snapc; struct inode* r_inode; } ;
struct ceph_osd_data {scalar_t__ type; struct page** pages; scalar_t__ pages_from_pool; scalar_t__ length; scalar_t__ alignment; } ;
struct ceph_inode_info {int dummy; } ;
struct ceph_fs_client {int blacklisted; TYPE_2__* mount_options; int /*<<< orphan*/  writeback_count; } ;
struct address_space {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  wb_pagevec_pool; } ;
struct TYPE_5__ {int /*<<< orphan*/  congestion_kb; } ;
struct TYPE_4__ {scalar_t__ op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_CAP_FILE_CACHE ; 
 int CEPH_CAP_FILE_LAZYIO ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_PAGES ; 
 scalar_t__ CEPH_OSD_OP_WRITE ; 
 scalar_t__ CONGESTION_OFF_THRESH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EBLACKLISTED ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_long_dec_return (int /*<<< orphan*/ *) ; 
 int calc_pages_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_caps_issued (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  ceph_clear_error_write (struct ceph_inode_info*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  ceph_put_snap_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_wrbuffer_cap_refs (struct ceph_inode_info*,int,struct ceph_snap_context*) ; 
 TYPE_3__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_set_error_write (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  clear_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  generic_error_remove_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 int /*<<< orphan*/  mempool_free (struct page**,int /*<<< orphan*/ ) ; 
 struct ceph_osd_data* osd_req_op_extent_osd_data (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  page_snap_context (struct page*) ; 
 int /*<<< orphan*/  release_pages (struct page**,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void writepages_finish(struct ceph_osd_request *req)
{
	struct inode *inode = req->r_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_osd_data *osd_data;
	struct page *page;
	int num_pages, total_pages = 0;
	int i, j;
	int rc = req->r_result;
	struct ceph_snap_context *snapc = req->r_snapc;
	struct address_space *mapping = inode->i_mapping;
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	bool remove_page;

	dout("writepages_finish %p rc %d\n", inode, rc);
	if (rc < 0) {
		mapping_set_error(mapping, rc);
		ceph_set_error_write(ci);
		if (rc == -EBLACKLISTED)
			fsc->blacklisted = true;
	} else {
		ceph_clear_error_write(ci);
	}

	/*
	 * We lost the cache cap, need to truncate the page before
	 * it is unlocked, otherwise we'd truncate it later in the
	 * page truncation thread, possibly losing some data that
	 * raced its way in
	 */
	remove_page = !(ceph_caps_issued(ci) &
			(CEPH_CAP_FILE_CACHE|CEPH_CAP_FILE_LAZYIO));

	/* clean all pages */
	for (i = 0; i < req->r_num_ops; i++) {
		if (req->r_ops[i].op != CEPH_OSD_OP_WRITE)
			break;

		osd_data = osd_req_op_extent_osd_data(req, i);
		BUG_ON(osd_data->type != CEPH_OSD_DATA_TYPE_PAGES);
		num_pages = calc_pages_for((u64)osd_data->alignment,
					   (u64)osd_data->length);
		total_pages += num_pages;
		for (j = 0; j < num_pages; j++) {
			page = osd_data->pages[j];
			BUG_ON(!page);
			WARN_ON(!PageUptodate(page));

			if (atomic_long_dec_return(&fsc->writeback_count) <
			     CONGESTION_OFF_THRESH(
					fsc->mount_options->congestion_kb))
				clear_bdi_congested(inode_to_bdi(inode),
						    BLK_RW_ASYNC);

			ceph_put_snap_context(page_snap_context(page));
			page->private = 0;
			ClearPagePrivate(page);
			dout("unlocking %p\n", page);
			end_page_writeback(page);

			if (remove_page)
				generic_error_remove_page(inode->i_mapping,
							  page);

			unlock_page(page);
		}
		dout("writepages_finish %p wrote %llu bytes cleaned %d pages\n",
		     inode, osd_data->length, rc >= 0 ? num_pages : 0);

		release_pages(osd_data->pages, num_pages);
	}

	ceph_put_wrbuffer_cap_refs(ci, total_pages, snapc);

	osd_data = osd_req_op_extent_osd_data(req, 0);
	if (osd_data->pages_from_pool)
		mempool_free(osd_data->pages,
			     ceph_sb_to_client(inode->i_sb)->wb_pagevec_pool);
	else
		kfree(osd_data->pages);
	ceph_osdc_put_request(req);
}