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
struct scsi_sge {int dummy; } ;
struct qedi_io_bdt {scalar_t__ sge_valid; int /*<<< orphan*/  sge_tbl; int /*<<< orphan*/  sge_tbl_dma; } ;
struct qedi_ctx {TYPE_1__* pdev; } ;
struct qedi_cmd {struct qedi_io_bdt io_tbl; } ;
struct iscsi_session {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int QEDI_ISCSI_MAX_BDS_PER_CMD ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_session_printk (int /*<<< orphan*/ ,struct iscsi_session*,char*) ; 

__attribute__((used)) static int qedi_alloc_sget(struct qedi_ctx *qedi, struct iscsi_session *session,
			   struct qedi_cmd *cmd)
{
	struct qedi_io_bdt *io = &cmd->io_tbl;
	struct scsi_sge *sge;

	io->sge_tbl = dma_alloc_coherent(&qedi->pdev->dev,
					 QEDI_ISCSI_MAX_BDS_PER_CMD *
					 sizeof(*sge),
					 &io->sge_tbl_dma, GFP_KERNEL);
	if (!io->sge_tbl) {
		iscsi_session_printk(KERN_ERR, session,
				     "Could not allocate BD table.\n");
		return -ENOMEM;
	}

	io->sge_valid = 0;
	return 0;
}