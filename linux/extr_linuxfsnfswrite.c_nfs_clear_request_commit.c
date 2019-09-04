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
struct nfs_page {int /*<<< orphan*/  wb_page; TYPE_1__* wb_context; int /*<<< orphan*/  wb_flags; } ;
struct nfs_commit_info {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PG_CLEAN ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_clear_page_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_inode (struct nfs_commit_info*,struct inode*) ; 
 int /*<<< orphan*/  nfs_request_remove_commit_list (struct nfs_page*,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  pnfs_clear_request_commit (struct nfs_page*,struct nfs_commit_info*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs_clear_request_commit(struct nfs_page *req)
{
	if (test_bit(PG_CLEAN, &req->wb_flags)) {
		struct inode *inode = d_inode(req->wb_context->dentry);
		struct nfs_commit_info cinfo;

		nfs_init_cinfo_from_inode(&cinfo, inode);
		mutex_lock(&NFS_I(inode)->commit_mutex);
		if (!pnfs_clear_request_commit(req, &cinfo)) {
			nfs_request_remove_commit_list(req, &cinfo);
		}
		mutex_unlock(&NFS_I(inode)->commit_mutex);
		nfs_clear_page_commit(req->wb_page);
	}
}