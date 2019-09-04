#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cmd_dma; int /*<<< orphan*/  timeout_sec; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp_len; int /*<<< orphan*/  cmd_len; scalar_t__ dl; scalar_t__ dir; struct nvmefc_ls_req* desc; } ;
struct TYPE_13__ {TYPE_3__ nvme; } ;
struct srb_iocb {TYPE_4__ u; } ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_nvme_rport {TYPE_6__* fcport; } ;
struct qla_hw_data {TYPE_2__* pdev; } ;
struct nvmefc_ls_req {int /*<<< orphan*/  rqstlen; int /*<<< orphan*/  rqstaddr; int /*<<< orphan*/  timeout; int /*<<< orphan*/  rspdma; int /*<<< orphan*/  rsplen; struct nvme_private* private; } ;
struct nvme_private {int /*<<< orphan*/  ls_work; struct nvmefc_ls_req* fd; TYPE_5__* sp; } ;
struct nvme_fc_remote_port {struct qla_nvme_rport* private; } ;
struct nvme_fc_local_port {int dummy; } ;
struct TYPE_10__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_14__ {char* name; int /*<<< orphan*/  nvme_ls_waitq; int /*<<< orphan*/  ref_count; TYPE_1__ u; int /*<<< orphan*/  done; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_15__ {struct scsi_qla_host* vha; } ;
typedef  TYPE_6__ fc_port_t ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_NVME_LS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 TYPE_5__* qla2x00_get_sp (struct scsi_qla_host*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int qla2x00_start_sp (TYPE_5__*) ; 
 int /*<<< orphan*/  qla_nvme_ls_complete ; 
 int /*<<< orphan*/  qla_nvme_sp_ls_done ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla_nvme_ls_req(struct nvme_fc_local_port *lport,
    struct nvme_fc_remote_port *rport, struct nvmefc_ls_req *fd)
{
	struct qla_nvme_rport *qla_rport = rport->private;
	fc_port_t *fcport = qla_rport->fcport;
	struct srb_iocb   *nvme;
	struct nvme_private *priv = fd->private;
	struct scsi_qla_host *vha;
	int     rval = QLA_FUNCTION_FAILED;
	struct qla_hw_data *ha;
	srb_t           *sp;

	vha = fcport->vha;
	ha = vha->hw;
	/* Alloc SRB structure */
	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	if (!sp)
		return rval;

	sp->type = SRB_NVME_LS;
	sp->name = "nvme_ls";
	sp->done = qla_nvme_sp_ls_done;
	atomic_set(&sp->ref_count, 1);
	nvme = &sp->u.iocb_cmd;
	priv->sp = sp;
	priv->fd = fd;
	INIT_WORK(&priv->ls_work, qla_nvme_ls_complete);
	nvme->u.nvme.desc = fd;
	nvme->u.nvme.dir = 0;
	nvme->u.nvme.dl = 0;
	nvme->u.nvme.cmd_len = fd->rqstlen;
	nvme->u.nvme.rsp_len = fd->rsplen;
	nvme->u.nvme.rsp_dma = fd->rspdma;
	nvme->u.nvme.timeout_sec = fd->timeout;
	nvme->u.nvme.cmd_dma = dma_map_single(&ha->pdev->dev, fd->rqstaddr,
	    fd->rqstlen, DMA_TO_DEVICE);
	dma_sync_single_for_device(&ha->pdev->dev, nvme->u.nvme.cmd_dma,
	    fd->rqstlen, DMA_TO_DEVICE);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x700e,
		    "qla2x00_start_sp failed = %d\n", rval);
		atomic_dec(&sp->ref_count);
		wake_up(&sp->nvme_ls_waitq);
		return rval;
	}

	return rval;
}