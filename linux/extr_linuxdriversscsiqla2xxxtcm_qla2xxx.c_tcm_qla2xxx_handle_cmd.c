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
typedef  int /*<<< orphan*/  uint32_t ;
struct se_session {int dummy; } ;
struct se_cmd {scalar_t__ cpuid; } ;
struct qla_tgt_cmd {int /*<<< orphan*/  unpacked_lun; int /*<<< orphan*/ * sense_buffer; TYPE_2__* qpair; struct fc_port* sess; struct se_cmd se_cmd; } ;
struct fc_port {struct se_session* se_sess; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_3__ {int /*<<< orphan*/  qla_core_sbt_cmd; } ;
struct TYPE_4__ {TYPE_1__ tgt_counters; } ;

/* Variables and functions */
 int EINVAL ; 
 int TARGET_SCF_ACK_KREF ; 
 int TARGET_SCF_BIDI_OP ; 
 int TARGET_SCF_USE_CPUID ; 
 scalar_t__ WORK_CPU_UNBOUND ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int target_submit_cmd (struct se_cmd*,struct se_session*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int tcm_qla2xxx_handle_cmd(scsi_qla_host_t *vha, struct qla_tgt_cmd *cmd,
	unsigned char *cdb, uint32_t data_length, int fcp_task_attr,
	int data_dir, int bidi)
{
	struct se_cmd *se_cmd = &cmd->se_cmd;
	struct se_session *se_sess;
	struct fc_port *sess;
#ifdef CONFIG_TCM_QLA2XXX_DEBUG
	struct se_portal_group *se_tpg;
	struct tcm_qla2xxx_tpg *tpg;
#endif
	int flags = TARGET_SCF_ACK_KREF;

	if (bidi)
		flags |= TARGET_SCF_BIDI_OP;

	if (se_cmd->cpuid != WORK_CPU_UNBOUND)
		flags |= TARGET_SCF_USE_CPUID;

	sess = cmd->sess;
	if (!sess) {
		pr_err("Unable to locate struct fc_port from qla_tgt_cmd\n");
		return -EINVAL;
	}

	se_sess = sess->se_sess;
	if (!se_sess) {
		pr_err("Unable to locate active struct se_session\n");
		return -EINVAL;
	}

#ifdef CONFIG_TCM_QLA2XXX_DEBUG
	se_tpg = se_sess->se_tpg;
	tpg = container_of(se_tpg, struct tcm_qla2xxx_tpg, se_tpg);
	if (unlikely(tpg->tpg_attrib.jam_host)) {
		/* return, and dont run target_submit_cmd,discarding command */
		return 0;
	}
#endif

	cmd->qpair->tgt_counters.qla_core_sbt_cmd++;
	return target_submit_cmd(se_cmd, se_sess, cdb, &cmd->sense_buffer[0],
				cmd->unpacked_lun, data_length, fcp_task_attr,
				data_dir, flags);
}