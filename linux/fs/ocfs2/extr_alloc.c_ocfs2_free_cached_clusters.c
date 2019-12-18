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
struct ocfs2_super {struct inode* osb_tl_inode; } ;
struct ocfs2_cached_block_free {struct ocfs2_cached_block_free* free_next; int /*<<< orphan*/  free_bit; int /*<<< orphan*/  free_blk; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_TRUNCATE_LOG_UPDATE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_cached_block_free*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_truncate_log_append (struct ocfs2_super*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_truncate_log_needs_flush (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_free_cached_clusters(struct ocfs2_super *osb,
				      struct ocfs2_cached_block_free *head)
{
	struct ocfs2_cached_block_free *tmp;
	struct inode *tl_inode = osb->osb_tl_inode;
	handle_t *handle;
	int ret = 0;

	inode_lock(tl_inode);

	while (head) {
		if (ocfs2_truncate_log_needs_flush(osb)) {
			ret = __ocfs2_flush_truncate_log(osb);
			if (ret < 0) {
				mlog_errno(ret);
				break;
			}
		}

		handle = ocfs2_start_trans(osb, OCFS2_TRUNCATE_LOG_UPDATE);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			mlog_errno(ret);
			break;
		}

		ret = ocfs2_truncate_log_append(osb, handle, head->free_blk,
						head->free_bit);

		ocfs2_commit_trans(osb, handle);
		tmp = head;
		head = head->free_next;
		kfree(tmp);

		if (ret < 0) {
			mlog_errno(ret);
			break;
		}
	}

	inode_unlock(tl_inode);

	while (head) {
		/* Premature exit may have left some dangling items. */
		tmp = head;
		head = head->free_next;
		kfree(tmp);
	}

	return ret;
}