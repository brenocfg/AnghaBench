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
struct nfs_page {int /*<<< orphan*/  wb_page; int /*<<< orphan*/  wb_bytes; TYPE_1__* wb_context; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 scalar_t__ NFS_FILEID (struct inode*) ; 
 int /*<<< orphan*/  PG_UNLOCKPAGE ; 
 scalar_t__ PageUptodate (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,long long) ; 
 scalar_t__ nfs_page_group_sync_on_bit (struct nfs_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_readpage_to_fscache (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_readpage_release(struct nfs_page *req)
{
	struct inode *inode = d_inode(req->wb_context->dentry);

	dprintk("NFS: read done (%s/%llu %d@%lld)\n", inode->i_sb->s_id,
		(unsigned long long)NFS_FILEID(inode), req->wb_bytes,
		(long long)req_offset(req));

	if (nfs_page_group_sync_on_bit(req, PG_UNLOCKPAGE)) {
		if (PageUptodate(req->wb_page))
			nfs_readpage_to_fscache(inode, req->wb_page, 0);

		unlock_page(req->wb_page);
	}
	nfs_release_request(req);
}