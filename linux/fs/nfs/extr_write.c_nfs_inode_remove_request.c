#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_page {int /*<<< orphan*/  wb_flags; scalar_t__ wb_page; struct nfs_page* wb_head; } ;
struct nfs_inode {int /*<<< orphan*/  nrequests; } ;
struct inode {int dummy; } ;
struct address_space {int /*<<< orphan*/  private_lock; struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (scalar_t__) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PG_INODE_REF ; 
 int /*<<< orphan*/  PG_MAPPED ; 
 int /*<<< orphan*/  PG_REMOVE ; 
 int /*<<< orphan*/  PageSwapCache (scalar_t__) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ nfs_page_group_sync_on_bit (struct nfs_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 struct address_space* page_file_mapping (scalar_t__) ; 
 int /*<<< orphan*/  set_page_private (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_inode_remove_request(struct nfs_page *req)
{
	struct address_space *mapping = page_file_mapping(req->wb_page);
	struct inode *inode = mapping->host;
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_page *head;

	if (nfs_page_group_sync_on_bit(req, PG_REMOVE)) {
		head = req->wb_head;

		spin_lock(&mapping->private_lock);
		if (likely(head->wb_page && !PageSwapCache(head->wb_page))) {
			set_page_private(head->wb_page, 0);
			ClearPagePrivate(head->wb_page);
			clear_bit(PG_MAPPED, &head->wb_flags);
		}
		spin_unlock(&mapping->private_lock);
	}

	if (test_and_clear_bit(PG_INODE_REF, &req->wb_flags)) {
		nfs_release_request(req);
		atomic_long_dec(&nfsi->nrequests);
	}
}