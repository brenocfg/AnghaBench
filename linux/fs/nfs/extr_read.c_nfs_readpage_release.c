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
struct page {int dummy; } ;
struct nfs_page {int /*<<< orphan*/  wb_bytes; struct page* wb_page; } ;
struct inode {TYPE_1__* i_sb; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ NFS_FILEID (struct inode*) ; 
 int /*<<< orphan*/  PG_UNLOCKPAGE ; 
 int /*<<< orphan*/  PageError (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  generic_error_remove_page (struct address_space*,struct page*) ; 
 scalar_t__ nfs_error_is_fatal_on_server (int) ; 
 scalar_t__ nfs_page_group_sync_on_bit (struct nfs_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_readpage_to_fscache (struct inode*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 TYPE_2__* nfs_req_openctx (struct nfs_page*) ; 
 struct address_space* page_file_mapping (struct page*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void nfs_readpage_release(struct nfs_page *req, int error)
{
	struct inode *inode = d_inode(nfs_req_openctx(req)->dentry);
	struct page *page = req->wb_page;

	dprintk("NFS: read done (%s/%llu %d@%lld)\n", inode->i_sb->s_id,
		(unsigned long long)NFS_FILEID(inode), req->wb_bytes,
		(long long)req_offset(req));

	if (nfs_error_is_fatal_on_server(error) && error != -ETIMEDOUT)
		SetPageError(page);
	if (nfs_page_group_sync_on_bit(req, PG_UNLOCKPAGE)) {
		struct address_space *mapping = page_file_mapping(page);

		if (PageUptodate(page))
			nfs_readpage_to_fscache(inode, page, 0);
		else if (!PageError(page) && !PagePrivate(page))
			generic_error_remove_page(mapping, page);
		unlock_page(page);
	}
	nfs_release_request(req);
}