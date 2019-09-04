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
struct scsi_qla_host {int dummy; } ;
struct qla_tgt_prm {int* sense_buffer; struct qla_tgt_cmd* cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  exchange_addr; } ;
struct TYPE_5__ {TYPE_1__ isp24; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct qla_tgt_cmd {int /*<<< orphan*/  cdb; TYPE_3__ atio; int /*<<< orphan*/  se_cmd; int /*<<< orphan*/  num_blks; int /*<<< orphan*/  lba; struct scsi_qla_host* vha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt_dif ; 
 int /*<<< orphan*/  ql_dump_buffer (int /*<<< orphan*/ ,struct scsi_qla_host*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qlt_print_dif_err(struct qla_tgt_prm *prm)
{
	struct qla_tgt_cmd *cmd;
	struct scsi_qla_host *vha;

	/* asc 0x10=dif error */
	if (prm->sense_buffer && (prm->sense_buffer[12] == 0x10)) {
		cmd = prm->cmd;
		vha = cmd->vha;
		/* ASCQ */
		switch (prm->sense_buffer[13]) {
		case 1:
			ql_dbg(ql_dbg_tgt_dif, vha, 0xe00b,
			    "BE detected Guard TAG ERR: lba[0x%llx|%lld] len[0x%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			break;
		case 2:
			ql_dbg(ql_dbg_tgt_dif, vha, 0xe00c,
			    "BE detected APP TAG ERR: lba[0x%llx|%lld] len[0x%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			break;
		case 3:
			ql_dbg(ql_dbg_tgt_dif, vha, 0xe00f,
			    "BE detected REF TAG ERR: lba[0x%llx|%lld] len[0x%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			break;
		default:
			ql_dbg(ql_dbg_tgt_dif, vha, 0xe010,
			    "BE detected Dif ERR: lba[%llx|%lld] len[%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			break;
		}
		ql_dump_buffer(ql_dbg_tgt_dif, vha, 0xe011, cmd->cdb, 16);
	}
}