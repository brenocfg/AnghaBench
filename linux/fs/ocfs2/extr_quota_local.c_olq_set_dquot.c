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
struct super_block {int dummy; } ;
struct ocfs2_local_disk_dqblk {void* dqb_inodemod; void* dqb_spacemod; void* dqb_id; } ;
struct TYPE_3__ {scalar_t__ dqb_curinodes; scalar_t__ dqb_curspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_dqb_lock; TYPE_1__ dq_dqb; struct super_block* dq_sb; } ;
struct ocfs2_dquot {TYPE_2__ dq_dquot; scalar_t__ dq_originodes; scalar_t__ dq_origspace; int /*<<< orphan*/  dq_local_off; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 void* cpu_to_le64 (scalar_t__) ; 
 scalar_t__ from_kqid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ le64_to_cpu (void*) ; 
 scalar_t__ ol_dqblk_block_offset (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_olq_set_dquot (unsigned long long,unsigned long long,scalar_t__) ; 

__attribute__((used)) static void olq_set_dquot(struct buffer_head *bh, void *private)
{
	struct ocfs2_dquot *od = private;
	struct ocfs2_local_disk_dqblk *dqblk;
	struct super_block *sb = od->dq_dquot.dq_sb;

	dqblk = (struct ocfs2_local_disk_dqblk *)(bh->b_data
		+ ol_dqblk_block_offset(sb, od->dq_local_off));

	dqblk->dqb_id = cpu_to_le64(from_kqid(&init_user_ns,
					      od->dq_dquot.dq_id));
	spin_lock(&od->dq_dquot.dq_dqb_lock);
	dqblk->dqb_spacemod = cpu_to_le64(od->dq_dquot.dq_dqb.dqb_curspace -
					  od->dq_origspace);
	dqblk->dqb_inodemod = cpu_to_le64(od->dq_dquot.dq_dqb.dqb_curinodes -
					  od->dq_originodes);
	spin_unlock(&od->dq_dquot.dq_dqb_lock);
	trace_olq_set_dquot(
		(unsigned long long)le64_to_cpu(dqblk->dqb_spacemod),
		(unsigned long long)le64_to_cpu(dqblk->dqb_inodemod),
		from_kqid(&init_user_ns, od->dq_dquot.dq_id));
}