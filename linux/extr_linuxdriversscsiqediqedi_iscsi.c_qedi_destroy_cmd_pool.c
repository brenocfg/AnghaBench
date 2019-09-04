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
struct scsi_sge {int dummy; } ;
struct qedi_ctx {TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  sge_tbl_dma; scalar_t__ sge_tbl; } ;
struct qedi_cmd {int /*<<< orphan*/  sense_buffer_dma; scalar_t__ sense_buffer; TYPE_1__ io_tbl; } ;
struct iscsi_task {struct qedi_cmd* dd_data; } ;
struct iscsi_session {int cmds_max; struct iscsi_task** cmds; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QEDI_ISCSI_MAX_BDS_PER_CMD ; 
 int SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedi_destroy_cmd_pool(struct qedi_ctx *qedi,
				  struct iscsi_session *session)
{
	int i;

	for (i = 0; i < session->cmds_max; i++) {
		struct iscsi_task *task = session->cmds[i];
		struct qedi_cmd *cmd = task->dd_data;

		if (cmd->io_tbl.sge_tbl)
			dma_free_coherent(&qedi->pdev->dev,
					  QEDI_ISCSI_MAX_BDS_PER_CMD *
					  sizeof(struct scsi_sge),
					  cmd->io_tbl.sge_tbl,
					  cmd->io_tbl.sge_tbl_dma);

		if (cmd->sense_buffer)
			dma_free_coherent(&qedi->pdev->dev,
					  SCSI_SENSE_BUFFERSIZE,
					  cmd->sense_buffer,
					  cmd->sense_buffer_dma);
	}
}