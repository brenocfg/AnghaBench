#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ocfs2_local_disk_chunk {int /*<<< orphan*/  dqc_free; int /*<<< orphan*/  dqc_bitmap; } ;
struct ocfs2_dquot {TYPE_2__* dq_chunk; int /*<<< orphan*/  dq_local_off; } ;
struct TYPE_8__ {int type; } ;
struct dquot {struct super_block* dq_sb; TYPE_1__ dq_id; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_11__ {int /*<<< orphan*/ * files; } ;
struct TYPE_10__ {scalar_t__ b_data; } ;
struct TYPE_9__ {TYPE_3__* qc_headerbh; int /*<<< orphan*/  qc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (int /*<<< orphan*/ ) ; 
 struct ocfs2_dquot* OCFS2_DQUOT (struct dquot*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_buffer (TYPE_3__*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_bit_unaligned (int,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_dq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int ol_dqblk_chunk_off (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  unlock_buffer (TYPE_3__*) ; 

int ocfs2_local_release_dquot(handle_t *handle, struct dquot *dquot)
{
	int status;
	int type = dquot->dq_id.type;
	struct ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	struct super_block *sb = dquot->dq_sb;
	struct ocfs2_local_disk_chunk *dchunk;
	int offset;

	status = ocfs2_journal_access_dq(handle,
			INODE_CACHE(sb_dqopt(sb)->files[type]),
			od->dq_chunk->qc_headerbh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}
	offset = ol_dqblk_chunk_off(sb, od->dq_chunk->qc_num,
					     od->dq_local_off);
	dchunk = (struct ocfs2_local_disk_chunk *)
			(od->dq_chunk->qc_headerbh->b_data);
	/* Mark structure as freed */
	lock_buffer(od->dq_chunk->qc_headerbh);
	ocfs2_clear_bit_unaligned(offset, dchunk->dqc_bitmap);
	le32_add_cpu(&dchunk->dqc_free, 1);
	unlock_buffer(od->dq_chunk->qc_headerbh);
	ocfs2_journal_dirty(handle, od->dq_chunk->qc_headerbh);

out:
	return status;
}