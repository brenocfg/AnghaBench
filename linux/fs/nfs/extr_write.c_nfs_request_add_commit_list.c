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
struct nfs_page {scalar_t__ wb_page; } ;
struct nfs_commit_info {int /*<<< orphan*/  inode; TYPE_1__* mds; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mark_page_unstable (scalar_t__,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_request_add_commit_list_locked (struct nfs_page*,int /*<<< orphan*/ *,struct nfs_commit_info*) ; 

void
nfs_request_add_commit_list(struct nfs_page *req, struct nfs_commit_info *cinfo)
{
	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	nfs_request_add_commit_list_locked(req, &cinfo->mds->list, cinfo);
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	if (req->wb_page)
		nfs_mark_page_unstable(req->wb_page, cinfo);
}