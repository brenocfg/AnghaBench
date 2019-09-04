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
struct ocfs2_super {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct dquot {int /*<<< orphan*/  dq_sb; TYPE_2__ dq_id; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  dqio_sem; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_QWRITE_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_local_write_dquot (struct dquot*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_write_dquot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_write_dquot(struct dquot *dquot)
{
	handle_t *handle;
	struct ocfs2_super *osb = OCFS2_SB(dquot->dq_sb);
	int status = 0;

	trace_ocfs2_write_dquot(from_kqid(&init_user_ns, dquot->dq_id),
				dquot->dq_id.type);

	handle = ocfs2_start_trans(osb, OCFS2_QWRITE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out;
	}
	down_write(&sb_dqopt(dquot->dq_sb)->dqio_sem);
	status = ocfs2_local_write_dquot(dquot);
	up_write(&sb_dqopt(dquot->dq_sb)->dqio_sem);
	ocfs2_commit_trans(osb, handle);
out:
	return status;
}