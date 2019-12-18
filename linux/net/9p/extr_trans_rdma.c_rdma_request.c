#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct p9_trans_rdma {scalar_t__ state; int /*<<< orphan*/  req_lock; TYPE_5__* cm_id; int /*<<< orphan*/  excess_rc; int /*<<< orphan*/  qp; int /*<<< orphan*/  sq_sem; TYPE_3__* pd; int /*<<< orphan*/  rq_sem; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  sdata; } ;
struct TYPE_12__ {int /*<<< orphan*/ * sdata; } ;
struct p9_req_t {int /*<<< orphan*/  status; TYPE_2__ tc; TYPE_6__ rc; } ;
struct TYPE_10__ {int /*<<< orphan*/  done; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sdata; } ;
struct p9_rdma_context {TYPE_4__ cqe; struct p9_req_t* req; int /*<<< orphan*/  busa; TYPE_1__ rc; } ;
struct p9_client {struct p9_trans_rdma* trans; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ib_send_wr {int num_sge; struct ib_sge* sg_list; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; TYPE_4__* wr_cqe; int /*<<< orphan*/ * next; } ;
struct TYPE_11__ {int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINTR ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 scalar_t__ P9_RDMA_CLOSING ; 
 int /*<<< orphan*/  REQ_STATUS_ERROR ; 
 int /*<<< orphan*/  REQ_STATUS_SENT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct p9_rdma_context*) ; 
 struct p9_rdma_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  p9_fcall_fini (TYPE_6__*) ; 
 int post_recv (struct p9_client*,struct p9_rdma_context*) ; 
 int /*<<< orphan*/  rdma_disconnect (TYPE_5__*) ; 
 int /*<<< orphan*/  send_done ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rdma_request(struct p9_client *client, struct p9_req_t *req)
{
	struct p9_trans_rdma *rdma = client->trans;
	struct ib_send_wr wr;
	struct ib_sge sge;
	int err = 0;
	unsigned long flags;
	struct p9_rdma_context *c = NULL;
	struct p9_rdma_context *rpl_context = NULL;

	/* When an error occurs between posting the recv and the send,
	 * there will be a receive context posted without a pending request.
	 * Since there is no way to "un-post" it, we remember it and skip
	 * post_recv() for the next request.
	 * So here,
	 * see if we are this `next request' and need to absorb an excess rc.
	 * If yes, then drop and free our own, and do not recv_post().
	 **/
	if (unlikely(atomic_read(&rdma->excess_rc) > 0)) {
		if ((atomic_sub_return(1, &rdma->excess_rc) >= 0)) {
			/* Got one! */
			p9_fcall_fini(&req->rc);
			req->rc.sdata = NULL;
			goto dont_need_post_recv;
		} else {
			/* We raced and lost. */
			atomic_inc(&rdma->excess_rc);
		}
	}

	/* Allocate an fcall for the reply */
	rpl_context = kmalloc(sizeof *rpl_context, GFP_NOFS);
	if (!rpl_context) {
		err = -ENOMEM;
		goto recv_error;
	}
	rpl_context->rc.sdata = req->rc.sdata;

	/*
	 * Post a receive buffer for this request. We need to ensure
	 * there is a reply buffer available for every outstanding
	 * request. A flushed request can result in no reply for an
	 * outstanding request, so we must keep a count to avoid
	 * overflowing the RQ.
	 */
	if (down_interruptible(&rdma->rq_sem)) {
		err = -EINTR;
		goto recv_error;
	}

	err = post_recv(client, rpl_context);
	if (err) {
		p9_debug(P9_DEBUG_ERROR, "POST RECV failed: %d\n", err);
		goto recv_error;
	}
	/* remove posted receive buffer from request structure */
	req->rc.sdata = NULL;

dont_need_post_recv:
	/* Post the request */
	c = kmalloc(sizeof *c, GFP_NOFS);
	if (!c) {
		err = -ENOMEM;
		goto send_error;
	}
	c->req = req;

	c->busa = ib_dma_map_single(rdma->cm_id->device,
				    c->req->tc.sdata, c->req->tc.size,
				    DMA_TO_DEVICE);
	if (ib_dma_mapping_error(rdma->cm_id->device, c->busa)) {
		err = -EIO;
		goto send_error;
	}

	c->cqe.done = send_done;

	sge.addr = c->busa;
	sge.length = c->req->tc.size;
	sge.lkey = rdma->pd->local_dma_lkey;

	wr.next = NULL;
	wr.wr_cqe = &c->cqe;
	wr.opcode = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;
	wr.sg_list = &sge;
	wr.num_sge = 1;

	if (down_interruptible(&rdma->sq_sem)) {
		err = -EINTR;
		goto send_error;
	}

	/* Mark request as `sent' *before* we actually send it,
	 * because doing if after could erase the REQ_STATUS_RCVD
	 * status in case of a very fast reply.
	 */
	req->status = REQ_STATUS_SENT;
	err = ib_post_send(rdma->qp, &wr, NULL);
	if (err)
		goto send_error;

	/* Success */
	return 0;

 /* Handle errors that happened during or while preparing the send: */
 send_error:
	req->status = REQ_STATUS_ERROR;
	kfree(c);
	p9_debug(P9_DEBUG_ERROR, "Error %d in rdma_request()\n", err);

	/* Ach.
	 *  We did recv_post(), but not send. We have one recv_post in excess.
	 */
	atomic_inc(&rdma->excess_rc);
	return err;

 /* Handle errors that happened during or while preparing post_recv(): */
 recv_error:
	kfree(rpl_context);
	spin_lock_irqsave(&rdma->req_lock, flags);
	if (err != -EINTR && rdma->state < P9_RDMA_CLOSING) {
		rdma->state = P9_RDMA_CLOSING;
		spin_unlock_irqrestore(&rdma->req_lock, flags);
		rdma_disconnect(rdma->cm_id);
	} else
		spin_unlock_irqrestore(&rdma->req_lock, flags);
	return err;
}