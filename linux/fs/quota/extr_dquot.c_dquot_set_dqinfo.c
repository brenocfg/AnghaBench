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
struct super_block {TYPE_2__* dq_op; } ;
struct qc_info {int i_fieldmask; int i_flags; int /*<<< orphan*/  i_ino_timelimit; int /*<<< orphan*/  i_spc_timelimit; } ;
struct mem_dqinfo {int /*<<< orphan*/  dqi_flags; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; TYPE_1__* dqi_format; } ;
struct TYPE_6__ {struct mem_dqinfo* info; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* write_info ) (struct super_block*,int) ;} ;
struct TYPE_4__ {scalar_t__ qf_fmt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQF_ROOT_SQUASH ; 
 int EINVAL ; 
 int ESRCH ; 
 int QCI_ROOT_SQUASH ; 
 int QC_FLAGS ; 
 int QC_INO_TIMER ; 
 int QC_RT_SPC_TIMER ; 
 int QC_SPC_TIMER ; 
 int QC_WARNS_MASK ; 
 scalar_t__ QFMT_VFS_OLD ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  mark_info_dirty (struct super_block*,int) ; 
 TYPE_3__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 

int dquot_set_dqinfo(struct super_block *sb, int type, struct qc_info *ii)
{
	struct mem_dqinfo *mi;
	int err = 0;

	if ((ii->i_fieldmask & QC_WARNS_MASK) ||
	    (ii->i_fieldmask & QC_RT_SPC_TIMER))
		return -EINVAL;
	if (!sb_has_quota_active(sb, type))
		return -ESRCH;
	mi = sb_dqopt(sb)->info + type;
	if (ii->i_fieldmask & QC_FLAGS) {
		if ((ii->i_flags & QCI_ROOT_SQUASH &&
		     mi->dqi_format->qf_fmt_id != QFMT_VFS_OLD))
			return -EINVAL;
	}
	spin_lock(&dq_data_lock);
	if (ii->i_fieldmask & QC_SPC_TIMER)
		mi->dqi_bgrace = ii->i_spc_timelimit;
	if (ii->i_fieldmask & QC_INO_TIMER)
		mi->dqi_igrace = ii->i_ino_timelimit;
	if (ii->i_fieldmask & QC_FLAGS) {
		if (ii->i_flags & QCI_ROOT_SQUASH)
			mi->dqi_flags |= DQF_ROOT_SQUASH;
		else
			mi->dqi_flags &= ~DQF_ROOT_SQUASH;
	}
	spin_unlock(&dq_data_lock);
	mark_info_dirty(sb, type);
	/* Force write to disk */
	sb->dq_op->write_info(sb, type);
	return err;
}