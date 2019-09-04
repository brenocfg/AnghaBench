#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_7__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  OCFS2_WINDOW_MOVE_CREDITS ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,TYPE_1__*) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_init_steal_slots (struct ocfs2_super*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 TYPE_1__* ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_sync_local_to_main (struct ocfs2_super*,TYPE_1__*,struct ocfs2_dinode*,struct inode*,struct buffer_head*) ; 

int ocfs2_complete_local_alloc_recovery(struct ocfs2_super *osb,
					struct ocfs2_dinode *alloc)
{
	int status;
	handle_t *handle;
	struct buffer_head *main_bm_bh = NULL;
	struct inode *main_bm_inode;

	main_bm_inode = ocfs2_get_system_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	if (!main_bm_inode) {
		status = -EINVAL;
		mlog_errno(status);
		goto out;
	}

	inode_lock(main_bm_inode);

	status = ocfs2_inode_lock(main_bm_inode, &main_bm_bh, 1);
	if (status < 0) {
		mlog_errno(status);
		goto out_mutex;
	}

	handle = ocfs2_start_trans(osb, OCFS2_WINDOW_MOVE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto out_unlock;
	}

	/* we want the bitmap change to be recorded on disk asap */
	handle->h_sync = 1;

	status = ocfs2_sync_local_to_main(osb, handle, alloc,
					  main_bm_inode, main_bm_bh);
	if (status < 0)
		mlog_errno(status);

	ocfs2_commit_trans(osb, handle);

out_unlock:
	ocfs2_inode_unlock(main_bm_inode, 1);

out_mutex:
	inode_unlock(main_bm_inode);

	brelse(main_bm_bh);

	iput(main_bm_inode);

out:
	if (!status)
		ocfs2_init_steal_slots(osb);
	if (status)
		mlog_errno(status);
	return status;
}