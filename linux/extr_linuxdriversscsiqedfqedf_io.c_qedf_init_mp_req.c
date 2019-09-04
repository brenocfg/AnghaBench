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
typedef  void* uint64_t ;
struct TYPE_6__ {void* hi; void* lo; } ;
struct scsi_sge {void* sge_len; TYPE_3__ sge_addr; } ;
struct qedf_mp_req {int req_len; int /*<<< orphan*/  resp_buf_dma; struct scsi_sge* mp_resp_bd; struct scsi_sge* mp_req_bd; int /*<<< orphan*/  req_buf_dma; int /*<<< orphan*/  mp_resp_bd_dma; int /*<<< orphan*/  mp_req_bd_dma; void* resp_buf; void* req_buf; } ;
struct qedf_ioreq {scalar_t__ cmd_type; int data_xfer_len; int /*<<< orphan*/  mp_req; TYPE_1__* fcport; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_2__* pdev; } ;
struct fcp_cmnd {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct qedf_ctx* qedf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ QEDF_ELS ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_MP_REQ ; 
 void* QEDF_PAGE_SIZE ; 
 void* U64_HI (int /*<<< orphan*/ ) ; 
 void* U64_LO (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qedf_mp_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedf_free_mp_resc (struct qedf_ioreq*) ; 

int qedf_init_mp_req(struct qedf_ioreq *io_req)
{
	struct qedf_mp_req *mp_req;
	struct scsi_sge *mp_req_bd;
	struct scsi_sge *mp_resp_bd;
	struct qedf_ctx *qedf = io_req->fcport->qedf;
	dma_addr_t addr;
	uint64_t sz;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_MP_REQ, "Entered.\n");

	mp_req = (struct qedf_mp_req *)&(io_req->mp_req);
	memset(mp_req, 0, sizeof(struct qedf_mp_req));

	if (io_req->cmd_type != QEDF_ELS) {
		mp_req->req_len = sizeof(struct fcp_cmnd);
		io_req->data_xfer_len = mp_req->req_len;
	} else
		mp_req->req_len = io_req->data_xfer_len;

	mp_req->req_buf = dma_alloc_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
	    &mp_req->req_buf_dma, GFP_KERNEL);
	if (!mp_req->req_buf) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc MP req buffer\n");
		qedf_free_mp_resc(io_req);
		return -ENOMEM;
	}

	mp_req->resp_buf = dma_alloc_coherent(&qedf->pdev->dev,
	    QEDF_PAGE_SIZE, &mp_req->resp_buf_dma, GFP_KERNEL);
	if (!mp_req->resp_buf) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc TM resp "
			  "buffer\n");
		qedf_free_mp_resc(io_req);
		return -ENOMEM;
	}

	/* Allocate and map mp_req_bd and mp_resp_bd */
	sz = sizeof(struct scsi_sge);
	mp_req->mp_req_bd = dma_alloc_coherent(&qedf->pdev->dev, sz,
	    &mp_req->mp_req_bd_dma, GFP_KERNEL);
	if (!mp_req->mp_req_bd) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc MP req bd\n");
		qedf_free_mp_resc(io_req);
		return -ENOMEM;
	}

	mp_req->mp_resp_bd = dma_alloc_coherent(&qedf->pdev->dev, sz,
	    &mp_req->mp_resp_bd_dma, GFP_KERNEL);
	if (!mp_req->mp_resp_bd) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to alloc MP resp bd\n");
		qedf_free_mp_resc(io_req);
		return -ENOMEM;
	}

	/* Fill bd table */
	addr = mp_req->req_buf_dma;
	mp_req_bd = mp_req->mp_req_bd;
	mp_req_bd->sge_addr.lo = U64_LO(addr);
	mp_req_bd->sge_addr.hi = U64_HI(addr);
	mp_req_bd->sge_len = QEDF_PAGE_SIZE;

	/*
	 * MP buffer is either a task mgmt command or an ELS.
	 * So the assumption is that it consumes a single bd
	 * entry in the bd table
	 */
	mp_resp_bd = mp_req->mp_resp_bd;
	addr = mp_req->resp_buf_dma;
	mp_resp_bd->sge_addr.lo = U64_LO(addr);
	mp_resp_bd->sge_addr.hi = U64_HI(addr);
	mp_resp_bd->sge_len = QEDF_PAGE_SIZE;

	return 0;
}