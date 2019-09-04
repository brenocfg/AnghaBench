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
struct nfs_page {int /*<<< orphan*/  wb_kref; int /*<<< orphan*/  wb_flags; int /*<<< orphan*/  wb_page; struct nfs_page* wb_this_page; } ;
struct nfs_inode {int /*<<< orphan*/  nrequests; } ;
struct inode {int dummy; } ;
struct address_space {int /*<<< orphan*/  private_lock; } ;
struct TYPE_2__ {scalar_t__ (* have_delegation ) (struct inode*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  PG_INODE_REF ; 
 int /*<<< orphan*/  PG_MAPPED ; 
 int /*<<< orphan*/  PageSwapCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPagePrivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_inc_iversion_raw (struct inode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  nfs_have_writebacks (struct inode*) ; 
 int /*<<< orphan*/  nfs_lock_request (struct nfs_page*) ; 
 struct address_space* page_file_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_inode_add_request(struct inode *inode, struct nfs_page *req)
{
	struct address_space *mapping = page_file_mapping(req->wb_page);
	struct nfs_inode *nfsi = NFS_I(inode);

	WARN_ON_ONCE(req->wb_this_page != req);

	/* Lock the request! */
	nfs_lock_request(req);

	/*
	 * Swap-space should not get truncated. Hence no need to plug the race
	 * with invalidate/truncate.
	 */
	spin_lock(&mapping->private_lock);
	if (!nfs_have_writebacks(inode) &&
	    NFS_PROTO(inode)->have_delegation(inode, FMODE_WRITE))
		inode_inc_iversion_raw(inode);
	if (likely(!PageSwapCache(req->wb_page))) {
		set_bit(PG_MAPPED, &req->wb_flags);
		SetPagePrivate(req->wb_page);
		set_page_private(req->wb_page, (unsigned long)req);
	}
	spin_unlock(&mapping->private_lock);
	atomic_long_inc(&nfsi->nrequests);
	/* this a head request for a page group - mark it as having an
	 * extra reference so sub groups can follow suit.
	 * This flag also informs pgio layer when to bump nrequests when
	 * adding subrequests. */
	WARN_ON(test_and_set_bit(PG_INODE_REF, &req->wb_flags));
	kref_get(&req->wb_kref);
}