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
struct super_block {int dummy; } ;
struct ocfs2_mem_dqinfo {int /*<<< orphan*/  dqi_gi; } ;
struct kqid {int type; } ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int ENOENT ; 
 int ESRCH ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,struct kqid) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int /*<<< orphan*/ ) ; 
 int ocfs2_qinfo_lock (struct ocfs2_mem_dqinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_qinfo_unlock (struct ocfs2_mem_dqinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int /*<<< orphan*/ ) ; 
 int qtree_get_next_id (int /*<<< orphan*/ *,struct kqid*) ; 
 TYPE_1__* sb_dqinfo (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_has_quota_loaded (struct super_block*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_get_next_id (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocfs2_get_next_id(struct super_block *sb, struct kqid *qid)
{
	int type = qid->type;
	struct ocfs2_mem_dqinfo *info = sb_dqinfo(sb, type)->dqi_priv;
	int status = 0;

	trace_ocfs2_get_next_id(from_kqid(&init_user_ns, *qid), type);
	if (!sb_has_quota_loaded(sb, type)) {
		status = -ESRCH;
		goto out;
	}
	status = ocfs2_lock_global_qf(info, 0);
	if (status < 0)
		goto out;
	status = ocfs2_qinfo_lock(info, 0);
	if (status < 0)
		goto out_global;
	status = qtree_get_next_id(&info->dqi_gi, qid);
	ocfs2_qinfo_unlock(info, 0);
out_global:
	ocfs2_unlock_global_qf(info, 0);
out:
	/*
	 * Avoid logging ENOENT since it just means there isn't next ID and
	 * ESRCH which means quota isn't enabled for the filesystem.
	 */
	if (status && status != -ENOENT && status != -ESRCH)
		mlog_errno(status);
	return status;
}