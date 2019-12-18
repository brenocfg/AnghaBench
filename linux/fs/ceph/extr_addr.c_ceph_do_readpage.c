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
typedef  scalar_t__ u64 ;
struct page {int /*<<< orphan*/  index; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct ceph_inode_info {scalar_t__ i_inline_version; int /*<<< orphan*/  i_truncate_size; int /*<<< orphan*/  i_truncate_seq; int /*<<< orphan*/  i_layout; } ;
struct ceph_fs_client {int blacklisted; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 scalar_t__ CEPH_INLINE_NONE ; 
 int EBLACKLISTED ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOENT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  ceph_fscache_readpage_cancel (struct inode*,struct page*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int ceph_osdc_readpages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page**,int,int /*<<< orphan*/ ) ; 
 int ceph_readpage_from_fscache (struct inode*,struct page*) ; 
 int /*<<< orphan*/  ceph_readpage_to_fscache (struct inode*,struct page*) ; 
 int /*<<< orphan*/  ceph_vino (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct file*,struct page*,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int,int) ; 

__attribute__((used)) static int ceph_do_readpage(struct file *filp, struct page *page)
{
	struct inode *inode = file_inode(filp);
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	int err = 0;
	u64 off = page_offset(page);
	u64 len = PAGE_SIZE;

	if (off >= i_size_read(inode)) {
		zero_user_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
		return 0;
	}

	if (ci->i_inline_version != CEPH_INLINE_NONE) {
		/*
		 * Uptodate inline data should have been added
		 * into page cache while getting Fcr caps.
		 */
		if (off == 0)
			return -EINVAL;
		zero_user_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
		return 0;
	}

	err = ceph_readpage_from_fscache(inode, page);
	if (err == 0)
		return -EINPROGRESS;

	dout("readpage inode %p file %p page %p index %lu\n",
	     inode, filp, page, page->index);
	err = ceph_osdc_readpages(&fsc->client->osdc, ceph_vino(inode),
				  &ci->i_layout, off, &len,
				  ci->i_truncate_seq, ci->i_truncate_size,
				  &page, 1, 0);
	if (err == -ENOENT)
		err = 0;
	if (err < 0) {
		SetPageError(page);
		ceph_fscache_readpage_cancel(inode, page);
		if (err == -EBLACKLISTED)
			fsc->blacklisted = true;
		goto out;
	}
	if (err < PAGE_SIZE)
		/* zero fill remainder of page */
		zero_user_segment(page, err, PAGE_SIZE);
	else
		flush_dcache_page(page);

	SetPageUptodate(page);
	ceph_readpage_to_fscache(inode, page);

out:
	return err < 0 ? err : 0;
}