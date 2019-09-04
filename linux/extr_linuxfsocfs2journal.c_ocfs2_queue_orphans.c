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
struct ocfs2_super {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  actor; } ;
struct ocfs2_orphan_filldir_priv {int orphan_reco_type; struct inode* head; TYPE_1__ ctx; struct ocfs2_super* osb; } ;
struct inode {int dummy; } ;
typedef  enum ocfs2_orphan_reco_type { ____Placeholder_ocfs2_orphan_reco_type } ocfs2_orphan_reco_type ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ORPHAN_DIR_SYSTEM_INODE ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dir_foreach (struct inode*,TYPE_1__*) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_orphan_filldir ; 

__attribute__((used)) static int ocfs2_queue_orphans(struct ocfs2_super *osb,
			       int slot,
			       struct inode **head,
			       enum ocfs2_orphan_reco_type orphan_reco_type)
{
	int status;
	struct inode *orphan_dir_inode = NULL;
	struct ocfs2_orphan_filldir_priv priv = {
		.ctx.actor = ocfs2_orphan_filldir,
		.osb = osb,
		.head = *head,
		.orphan_reco_type = orphan_reco_type
	};

	orphan_dir_inode = ocfs2_get_system_file_inode(osb,
						       ORPHAN_DIR_SYSTEM_INODE,
						       slot);
	if  (!orphan_dir_inode) {
		status = -ENOENT;
		mlog_errno(status);
		return status;
	}

	inode_lock(orphan_dir_inode);
	status = ocfs2_inode_lock(orphan_dir_inode, NULL, 0);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	status = ocfs2_dir_foreach(orphan_dir_inode, &priv.ctx);
	if (status) {
		mlog_errno(status);
		goto out_cluster;
	}

	*head = priv.head;

out_cluster:
	ocfs2_inode_unlock(orphan_dir_inode, 0);
out:
	inode_unlock(orphan_dir_inode);
	iput(orphan_dir_inode);
	return status;
}