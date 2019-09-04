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
struct super_block {int dummy; } ;
struct ocfs2_quota_chunk {int /*<<< orphan*/  qc_headerbh; int /*<<< orphan*/  qc_num; } ;
struct ocfs2_dquot {int /*<<< orphan*/  dq_local_phys_blk; struct ocfs2_quota_chunk* dq_chunk; int /*<<< orphan*/  dq_local_off; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int type; } ;
struct dquot {TYPE_1__ dq_id; struct super_block* dq_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip_alloc_sem; } ;
struct TYPE_5__ {struct inode** files; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ocfs2_quota_chunk*) ; 
 struct ocfs2_dquot* OCFS2_DQUOT (struct dquot*) ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int PTR_ERR (struct ocfs2_quota_chunk*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct ocfs2_quota_chunk* ocfs2_extend_local_quota_file (struct super_block*,int,int*) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ocfs2_quota_chunk* ocfs2_find_free_entry (struct super_block*,int,int*) ; 
 int ocfs2_local_write_dquot (struct dquot*) ; 
 int ocfs2_modify_bh (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ol_dqblk_block (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ol_dqblk_off (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  olq_alloc_dquot ; 
 TYPE_2__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ocfs2_create_local_dquot(struct dquot *dquot)
{
	struct super_block *sb = dquot->dq_sb;
	int type = dquot->dq_id.type;
	struct inode *lqinode = sb_dqopt(sb)->files[type];
	struct ocfs2_quota_chunk *chunk;
	struct ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	int offset;
	int status;
	u64 pcount;

	down_write(&OCFS2_I(lqinode)->ip_alloc_sem);
	chunk = ocfs2_find_free_entry(sb, type, &offset);
	if (!chunk) {
		chunk = ocfs2_extend_local_quota_file(sb, type, &offset);
		if (IS_ERR(chunk)) {
			status = PTR_ERR(chunk);
			goto out;
		}
	} else if (IS_ERR(chunk)) {
		status = PTR_ERR(chunk);
		goto out;
	}
	od->dq_local_off = ol_dqblk_off(sb, chunk->qc_num, offset);
	od->dq_chunk = chunk;
	status = ocfs2_extent_map_get_blocks(lqinode,
				     ol_dqblk_block(sb, chunk->qc_num, offset),
				     &od->dq_local_phys_blk,
				     &pcount,
				     NULL);

	/* Initialize dquot structure on disk */
	status = ocfs2_local_write_dquot(dquot);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	/* Mark structure as allocated */
	status = ocfs2_modify_bh(lqinode, chunk->qc_headerbh, olq_alloc_dquot,
				 &offset);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}
out:
	up_write(&OCFS2_I(lqinode)->ip_alloc_sem);
	return status;
}