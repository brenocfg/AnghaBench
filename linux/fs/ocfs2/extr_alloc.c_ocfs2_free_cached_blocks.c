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
typedef  scalar_t__ u64 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_cached_block_free {struct ocfs2_cached_block_free* free_next; int /*<<< orphan*/  free_bit; scalar_t__ free_blk; scalar_t__ free_bg; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_SUBALLOC_FREE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_cached_block_free*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int,int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_which_suballoc_group (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_free_cached_blocks (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_free_cached_blocks(struct ocfs2_super *osb,
				    int sysfile_type,
				    int slot,
				    struct ocfs2_cached_block_free *head)
{
	int ret;
	u64 bg_blkno;
	handle_t *handle;
	struct inode *inode;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_cached_block_free *tmp;

	inode = ocfs2_get_system_file_inode(osb, sysfile_type, slot);
	if (!inode) {
		ret = -EINVAL;
		mlog_errno(ret);
		goto out;
	}

	inode_lock(inode);

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	if (ret) {
		mlog_errno(ret);
		goto out_mutex;
	}

	while (head) {
		if (head->free_bg)
			bg_blkno = head->free_bg;
		else
			bg_blkno = ocfs2_which_suballoc_group(head->free_blk,
							      head->free_bit);
		handle = ocfs2_start_trans(osb, OCFS2_SUBALLOC_FREE);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			mlog_errno(ret);
			goto out_unlock;
		}

		trace_ocfs2_free_cached_blocks(
		     (unsigned long long)head->free_blk, head->free_bit);

		ret = ocfs2_free_suballoc_bits(handle, inode, di_bh,
					       head->free_bit, bg_blkno, 1);
		if (ret)
			mlog_errno(ret);

		ocfs2_commit_trans(osb, handle);

		tmp = head;
		head = head->free_next;
		kfree(tmp);
	}

out_unlock:
	ocfs2_inode_unlock(inode, 1);
	brelse(di_bh);
out_mutex:
	inode_unlock(inode);
	iput(inode);
out:
	while(head) {
		/* Premature exit may have left some dangling items. */
		tmp = head;
		head = head->free_next;
		kfree(tmp);
	}

	return ret;
}