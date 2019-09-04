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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u64 ;
struct se_cmd {int dummy; } ;
struct qla_tgt_mgmt_cmd {struct se_cmd se_cmd; struct fc_port* sess; } ;
struct fc_port {int /*<<< orphan*/  se_sess; TYPE_1__* vha; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  QLA_TGT_2G_ABORT_TASK 134 
#define  QLA_TGT_ABORT_TS 133 
#define  QLA_TGT_ABTS 132 
#define  QLA_TGT_CLEAR_ACA 131 
#define  QLA_TGT_CLEAR_TS 130 
#define  QLA_TGT_LUN_RESET 129 
#define  QLA_TGT_TARGET_RESET 128 
 int TARGET_SCF_ACK_KREF ; 
 int TARGET_SCF_LOOKUP_LUN_FROM_TAG ; 
 int TMR_ABORT_TASK ; 
 int TMR_ABORT_TASK_SET ; 
 int TMR_CLEAR_ACA ; 
 int TMR_CLEAR_TASK_SET ; 
 int TMR_LUN_RESET ; 
 int TMR_TARGET_WARM_RESET ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int target_submit_tmr (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct qla_tgt_mgmt_cmd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcm_qla2xxx_handle_tmr(struct qla_tgt_mgmt_cmd *mcmd, u64 lun,
	uint16_t tmr_func, uint32_t tag)
{
	struct fc_port *sess = mcmd->sess;
	struct se_cmd *se_cmd = &mcmd->se_cmd;
	int transl_tmr_func = 0;
	int flags = TARGET_SCF_ACK_KREF;

	switch (tmr_func) {
	case QLA_TGT_ABTS:
		pr_debug("%ld: ABTS received\n", sess->vha->host_no);
		transl_tmr_func = TMR_ABORT_TASK;
		flags |= TARGET_SCF_LOOKUP_LUN_FROM_TAG;
		break;
	case QLA_TGT_2G_ABORT_TASK:
		pr_debug("%ld: 2G Abort Task received\n", sess->vha->host_no);
		transl_tmr_func = TMR_ABORT_TASK;
		break;
	case QLA_TGT_CLEAR_ACA:
		pr_debug("%ld: CLEAR_ACA received\n", sess->vha->host_no);
		transl_tmr_func = TMR_CLEAR_ACA;
		break;
	case QLA_TGT_TARGET_RESET:
		pr_debug("%ld: TARGET_RESET received\n", sess->vha->host_no);
		transl_tmr_func = TMR_TARGET_WARM_RESET;
		break;
	case QLA_TGT_LUN_RESET:
		pr_debug("%ld: LUN_RESET received\n", sess->vha->host_no);
		transl_tmr_func = TMR_LUN_RESET;
		break;
	case QLA_TGT_CLEAR_TS:
		pr_debug("%ld: CLEAR_TS received\n", sess->vha->host_no);
		transl_tmr_func = TMR_CLEAR_TASK_SET;
		break;
	case QLA_TGT_ABORT_TS:
		pr_debug("%ld: ABORT_TS received\n", sess->vha->host_no);
		transl_tmr_func = TMR_ABORT_TASK_SET;
		break;
	default:
		pr_debug("%ld: Unknown task mgmt fn 0x%x\n",
		    sess->vha->host_no, tmr_func);
		return -ENOSYS;
	}

	return target_submit_tmr(se_cmd, sess->se_sess, NULL, lun, mcmd,
	    transl_tmr_func, GFP_ATOMIC, tag, flags);
}