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
struct nfs_commit_info {int /*<<< orphan*/  inode; TYPE_1__* mds; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_scan_commit_list (int /*<<< orphan*/ *,struct list_head*,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_direct_write_scan_commit_list(struct inode *inode,
				  struct list_head *list,
				  struct nfs_commit_info *cinfo)
{
	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
#ifdef CONFIG_NFS_V4_1
	if (cinfo->ds != NULL && cinfo->ds->nwritten != 0)
		NFS_SERVER(inode)->pnfs_curr_ld->recover_commit_reqs(list, cinfo);
#endif
	nfs_scan_commit_list(&cinfo->mds->list, list, cinfo, 0);
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
}