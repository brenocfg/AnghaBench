#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_tgt_cmd {TYPE_1__* ctx; scalar_t__ ctx_dsd_alloced; int /*<<< orphan*/  dma_data_direction; int /*<<< orphan*/  prot_sg_cnt; int /*<<< orphan*/  prot_sg; scalar_t__ sg_mapped; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg; struct qla_qpair* qpair; } ;
struct qla_qpair {int /*<<< orphan*/  pdev; } ;
struct qla_hw_data {int /*<<< orphan*/  dl_dma_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  crc_ctx_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_clean_dsd_pool (struct qla_hw_data*,TYPE_1__*) ; 

__attribute__((used)) static void qlt_unmap_sg(struct scsi_qla_host *vha, struct qla_tgt_cmd *cmd)
{
	struct qla_hw_data *ha;
	struct qla_qpair *qpair;
	if (!cmd->sg_mapped)
		return;

	qpair = cmd->qpair;

	pci_unmap_sg(qpair->pdev, cmd->sg, cmd->sg_cnt,
	    cmd->dma_data_direction);
	cmd->sg_mapped = 0;

	if (cmd->prot_sg_cnt)
		pci_unmap_sg(qpair->pdev, cmd->prot_sg, cmd->prot_sg_cnt,
			cmd->dma_data_direction);

	if (!cmd->ctx)
		return;
	ha = vha->hw;
	if (cmd->ctx_dsd_alloced)
		qla2x00_clean_dsd_pool(ha, cmd->ctx);

	dma_pool_free(ha->dl_dma_pool, cmd->ctx, cmd->ctx->crc_ctx_dma);
}