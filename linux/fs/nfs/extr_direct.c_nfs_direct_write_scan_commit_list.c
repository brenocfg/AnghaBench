#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_commit_info {int /*<<< orphan*/  inode; TYPE_2__* mds; TYPE_3__* ds; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  commit_mutex; } ;
struct TYPE_9__ {TYPE_1__* pnfs_curr_ld; } ;
struct TYPE_8__ {scalar_t__ nwritten; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* recover_commit_reqs ) (struct list_head*,struct nfs_commit_info*) ;} ;

/* Variables and functions */
 TYPE_5__* NFS_I (int /*<<< orphan*/ ) ; 
 TYPE_4__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_scan_commit_list (int /*<<< orphan*/ *,struct list_head*,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct list_head*,struct nfs_commit_info*) ; 

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