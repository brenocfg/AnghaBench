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
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  ncommit; } ;

/* Variables and functions */
 int INT_MAX ; 
 TYPE_2__* NFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nfs_scan_commit_list (int /*<<< orphan*/ *,struct list_head*,struct nfs_commit_info*,int const) ; 
 scalar_t__ pnfs_scan_commit_lists (struct inode*,struct nfs_commit_info*,int const) ; 

int
nfs_scan_commit(struct inode *inode, struct list_head *dst,
		struct nfs_commit_info *cinfo)
{
	int ret = 0;

	if (!atomic_long_read(&cinfo->mds->ncommit))
		return 0;
	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	if (atomic_long_read(&cinfo->mds->ncommit) > 0) {
		const int max = INT_MAX;

		ret = nfs_scan_commit_list(&cinfo->mds->list, dst,
					   cinfo, max);
		ret += pnfs_scan_commit_lists(inode, cinfo, max - ret);
	}
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	return ret;
}