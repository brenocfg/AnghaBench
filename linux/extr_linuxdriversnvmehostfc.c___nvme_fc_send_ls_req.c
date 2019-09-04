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
struct nvmefc_ls_req {void (* done ) (struct nvmefc_ls_req*,int) ;scalar_t__ rsplen; scalar_t__ rqstlen; scalar_t__ rqstdma; scalar_t__ rspdma; int /*<<< orphan*/  rqstaddr; } ;
struct nvmefc_ls_req_op {int req_queued; int ls_error; int /*<<< orphan*/  lsreq_list; int /*<<< orphan*/  ls_done; struct nvme_fc_rport* rport; struct nvmefc_ls_req ls_req; } ;
struct TYPE_6__ {scalar_t__ port_state; } ;
struct nvme_fc_rport {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_3__ remoteport; TYPE_2__* lport; int /*<<< orphan*/  ls_req_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  localport; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* ls_req ) (int /*<<< orphan*/ *,TYPE_3__*,struct nvmefc_ls_req*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ECONNREFUSED ; 
 int EFAULT ; 
 int ESHUTDOWN ; 
 scalar_t__ FC_OBJSTATE_ONLINE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ fc_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fc_dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fc_dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_fc_rport_get (struct nvme_fc_rport*) ; 
 int /*<<< orphan*/  nvme_fc_rport_put (struct nvme_fc_rport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_3__*,struct nvmefc_ls_req*) ; 

__attribute__((used)) static int
__nvme_fc_send_ls_req(struct nvme_fc_rport *rport,
		struct nvmefc_ls_req_op *lsop,
		void (*done)(struct nvmefc_ls_req *req, int status))
{
	struct nvmefc_ls_req *lsreq = &lsop->ls_req;
	unsigned long flags;
	int ret = 0;

	if (rport->remoteport.port_state != FC_OBJSTATE_ONLINE)
		return -ECONNREFUSED;

	if (!nvme_fc_rport_get(rport))
		return -ESHUTDOWN;

	lsreq->done = done;
	lsop->rport = rport;
	lsop->req_queued = false;
	INIT_LIST_HEAD(&lsop->lsreq_list);
	init_completion(&lsop->ls_done);

	lsreq->rqstdma = fc_dma_map_single(rport->dev, lsreq->rqstaddr,
				  lsreq->rqstlen + lsreq->rsplen,
				  DMA_BIDIRECTIONAL);
	if (fc_dma_mapping_error(rport->dev, lsreq->rqstdma)) {
		ret = -EFAULT;
		goto out_putrport;
	}
	lsreq->rspdma = lsreq->rqstdma + lsreq->rqstlen;

	spin_lock_irqsave(&rport->lock, flags);

	list_add_tail(&lsop->lsreq_list, &rport->ls_req_list);

	lsop->req_queued = true;

	spin_unlock_irqrestore(&rport->lock, flags);

	ret = rport->lport->ops->ls_req(&rport->lport->localport,
					&rport->remoteport, lsreq);
	if (ret)
		goto out_unlink;

	return 0;

out_unlink:
	lsop->ls_error = ret;
	spin_lock_irqsave(&rport->lock, flags);
	lsop->req_queued = false;
	list_del(&lsop->lsreq_list);
	spin_unlock_irqrestore(&rport->lock, flags);
	fc_dma_unmap_single(rport->dev, lsreq->rqstdma,
				  (lsreq->rqstlen + lsreq->rsplen),
				  DMA_BIDIRECTIONAL);
out_putrport:
	nvme_fc_rport_put(rport);

	return ret;
}