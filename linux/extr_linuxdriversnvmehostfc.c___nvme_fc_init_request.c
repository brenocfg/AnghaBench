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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct request {int dummy; } ;
struct nvme_fc_queue {int dummy; } ;
struct TYPE_4__ {int cmdlen; int rsplen; void* rspdma; void* cmddma; struct scatterlist* first_sgl; struct scatterlist* private; int /*<<< orphan*/  done; struct nvme_fc_cmd_iu* rspaddr; struct nvme_fc_cmd_iu* cmdaddr; } ;
struct nvme_fc_cmd_iu {int /*<<< orphan*/  iu_len; int /*<<< orphan*/  fc_id; int /*<<< orphan*/  scsi_id; } ;
struct nvme_fc_fcp_op {int /*<<< orphan*/  state; TYPE_2__ fcp_req; struct nvme_fc_cmd_iu rsp_iu; struct nvme_fc_cmd_iu cmd_iu; int /*<<< orphan*/  rqno; struct request* rq; struct nvme_fc_queue* queue; struct nvme_fc_ctrl* ctrl; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  dev; TYPE_1__* lport; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int /*<<< orphan*/  FCPOP_STATE_IDLE ; 
 int /*<<< orphan*/  NVME_CMD_FC_ID ; 
 int /*<<< orphan*/  NVME_CMD_SCSI_ID ; 
 size_t SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* fc_dma_map_single (int /*<<< orphan*/ ,struct nvme_fc_cmd_iu*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fc_dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (struct nvme_fc_fcp_op*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_fc_fcpio_done ; 

__attribute__((used)) static int
__nvme_fc_init_request(struct nvme_fc_ctrl *ctrl,
		struct nvme_fc_queue *queue, struct nvme_fc_fcp_op *op,
		struct request *rq, u32 rqno)
{
	struct nvme_fc_cmd_iu *cmdiu = &op->cmd_iu;
	int ret = 0;

	memset(op, 0, sizeof(*op));
	op->fcp_req.cmdaddr = &op->cmd_iu;
	op->fcp_req.cmdlen = sizeof(op->cmd_iu);
	op->fcp_req.rspaddr = &op->rsp_iu;
	op->fcp_req.rsplen = sizeof(op->rsp_iu);
	op->fcp_req.done = nvme_fc_fcpio_done;
	op->fcp_req.first_sgl = (struct scatterlist *)&op[1];
	op->fcp_req.private = &op->fcp_req.first_sgl[SG_CHUNK_SIZE];
	op->ctrl = ctrl;
	op->queue = queue;
	op->rq = rq;
	op->rqno = rqno;

	cmdiu->scsi_id = NVME_CMD_SCSI_ID;
	cmdiu->fc_id = NVME_CMD_FC_ID;
	cmdiu->iu_len = cpu_to_be16(sizeof(*cmdiu) / sizeof(u32));

	op->fcp_req.cmddma = fc_dma_map_single(ctrl->lport->dev,
				&op->cmd_iu, sizeof(op->cmd_iu), DMA_TO_DEVICE);
	if (fc_dma_mapping_error(ctrl->lport->dev, op->fcp_req.cmddma)) {
		dev_err(ctrl->dev,
			"FCP Op failed - cmdiu dma mapping failed.\n");
		ret = EFAULT;
		goto out_on_error;
	}

	op->fcp_req.rspdma = fc_dma_map_single(ctrl->lport->dev,
				&op->rsp_iu, sizeof(op->rsp_iu),
				DMA_FROM_DEVICE);
	if (fc_dma_mapping_error(ctrl->lport->dev, op->fcp_req.rspdma)) {
		dev_err(ctrl->dev,
			"FCP Op failed - rspiu dma mapping failed.\n");
		ret = EFAULT;
	}

	atomic_set(&op->state, FCPOP_STATE_IDLE);
out_on_error:
	return ret;
}