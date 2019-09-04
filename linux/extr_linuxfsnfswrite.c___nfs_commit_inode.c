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
struct writeback_control {scalar_t__ sync_mode; int nr_to_write; } ;
struct nfs_commit_info {int /*<<< orphan*/  mds; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int FLUSH_SYNC ; 
 int INT_MAX ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_NONE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  nfs_commit_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_commit_end (int /*<<< orphan*/ ) ; 
 int nfs_generic_commit_list (struct inode*,int /*<<< orphan*/ *,int,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_inode (struct nfs_commit_info*,struct inode*) ; 
 int nfs_scan_commit (struct inode*,int /*<<< orphan*/ *,struct nfs_commit_info*) ; 
 int wait_on_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nfs_commit_inode(struct inode *inode, int how,
		struct writeback_control *wbc)
{
	LIST_HEAD(head);
	struct nfs_commit_info cinfo;
	int may_wait = how & FLUSH_SYNC;
	int ret, nscan;

	nfs_init_cinfo_from_inode(&cinfo, inode);
	nfs_commit_begin(cinfo.mds);
	for (;;) {
		ret = nscan = nfs_scan_commit(inode, &head, &cinfo);
		if (ret <= 0)
			break;
		ret = nfs_generic_commit_list(inode, &head, how, &cinfo);
		if (ret < 0)
			break;
		ret = 0;
		if (wbc && wbc->sync_mode == WB_SYNC_NONE) {
			if (nscan < wbc->nr_to_write)
				wbc->nr_to_write -= nscan;
			else
				wbc->nr_to_write = 0;
		}
		if (nscan < INT_MAX)
			break;
		cond_resched();
	}
	nfs_commit_end(cinfo.mds);
	if (ret || !may_wait)
		return ret;
	return wait_on_commit(cinfo.mds);
}