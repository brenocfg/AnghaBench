#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fce_enabled; } ;
struct qla_hw_data {int /*<<< orphan*/  fce_mutex; TYPE_1__ flags; int /*<<< orphan*/  fce_rd; int /*<<< orphan*/  fce_wr; } ;
struct inode {TYPE_2__* i_private; } ;
struct file {int dummy; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  qla2x00_dfs_fce_show ; 
 int qla2x00_disable_fce_trace (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int single_open (struct file*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
qla2x00_dfs_fce_open(struct inode *inode, struct file *file)
{
	scsi_qla_host_t *vha = inode->i_private;
	struct qla_hw_data *ha = vha->hw;
	int rval;

	if (!ha->flags.fce_enabled)
		goto out;

	mutex_lock(&ha->fce_mutex);

	/* Pause tracing to flush FCE buffers. */
	rval = qla2x00_disable_fce_trace(vha, &ha->fce_wr, &ha->fce_rd);
	if (rval)
		ql_dbg(ql_dbg_user, vha, 0x705c,
		    "DebugFS: Unable to disable FCE (%d).\n", rval);

	ha->flags.fce_enabled = 0;

	mutex_unlock(&ha->fce_mutex);
out:
	return single_open(file, qla2x00_dfs_fce_show, vha);
}