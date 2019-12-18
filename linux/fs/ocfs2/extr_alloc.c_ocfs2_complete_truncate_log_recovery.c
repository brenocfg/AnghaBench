#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_truncate_log {TYPE_2__* tl_recs; int /*<<< orphan*/  tl_used; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; struct inode* osb_tl_inode; } ;
struct TYPE_4__ {struct ocfs2_truncate_log i_dealloc; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_blkno; TYPE_1__ id2; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {scalar_t__ ip_blkno; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_start; int /*<<< orphan*/  t_clusters; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_TRUNCATE_LOG_UPDATE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_truncate_log_append (struct ocfs2_super*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ocfs2_truncate_log_needs_flush (struct ocfs2_super*) ; 
 int /*<<< orphan*/  trace_ocfs2_complete_truncate_log_recovery (unsigned long long,unsigned int) ; 

int ocfs2_complete_truncate_log_recovery(struct ocfs2_super *osb,
					 struct ocfs2_dinode *tl_copy)
{
	int status = 0;
	int i;
	unsigned int clusters, num_recs, start_cluster;
	u64 start_blk;
	handle_t *handle;
	struct inode *tl_inode = osb->osb_tl_inode;
	struct ocfs2_truncate_log *tl;

	if (OCFS2_I(tl_inode)->ip_blkno == le64_to_cpu(tl_copy->i_blkno)) {
		mlog(ML_ERROR, "Asked to recover my own truncate log!\n");
		return -EINVAL;
	}

	tl = &tl_copy->id2.i_dealloc;
	num_recs = le16_to_cpu(tl->tl_used);
	trace_ocfs2_complete_truncate_log_recovery(
		(unsigned long long)le64_to_cpu(tl_copy->i_blkno),
		num_recs);

	inode_lock(tl_inode);
	for(i = 0; i < num_recs; i++) {
		if (ocfs2_truncate_log_needs_flush(osb)) {
			status = __ocfs2_flush_truncate_log(osb);
			if (status < 0) {
				mlog_errno(status);
				goto bail_up;
			}
		}

		handle = ocfs2_start_trans(osb, OCFS2_TRUNCATE_LOG_UPDATE);
		if (IS_ERR(handle)) {
			status = PTR_ERR(handle);
			mlog_errno(status);
			goto bail_up;
		}

		clusters = le32_to_cpu(tl->tl_recs[i].t_clusters);
		start_cluster = le32_to_cpu(tl->tl_recs[i].t_start);
		start_blk = ocfs2_clusters_to_blocks(osb->sb, start_cluster);

		status = ocfs2_truncate_log_append(osb, handle,
						   start_blk, clusters);
		ocfs2_commit_trans(osb, handle);
		if (status < 0) {
			mlog_errno(status);
			goto bail_up;
		}
	}

bail_up:
	inode_unlock(tl_inode);

	return status;
}