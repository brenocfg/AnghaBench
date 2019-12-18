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
struct virtio_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  vq; scalar_t__ ring_bufs_avail; int /*<<< orphan*/ * vc_wq; struct scatterlist* sg; } ;
struct scatterlist {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  capacity; int /*<<< orphan*/  sdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  sdata; } ;
struct p9_req_t {TYPE_2__ rc; TYPE_1__ tc; int /*<<< orphan*/  status; } ;
struct p9_client {struct virtio_chan* trans; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  REQ_STATUS_SENT ; 
 int /*<<< orphan*/  VIRTQUEUE_NUM ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int pack_sg_list (struct scatterlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virtqueue_add_sgs (int /*<<< orphan*/ ,struct scatterlist**,int,int,struct p9_req_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 
 int wait_event_killable (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
p9_virtio_request(struct p9_client *client, struct p9_req_t *req)
{
	int err;
	int in, out, out_sgs, in_sgs;
	unsigned long flags;
	struct virtio_chan *chan = client->trans;
	struct scatterlist *sgs[2];

	p9_debug(P9_DEBUG_TRANS, "9p debug: virtio request\n");

	req->status = REQ_STATUS_SENT;
req_retry:
	spin_lock_irqsave(&chan->lock, flags);

	out_sgs = in_sgs = 0;
	/* Handle out VirtIO ring buffers */
	out = pack_sg_list(chan->sg, 0,
			   VIRTQUEUE_NUM, req->tc.sdata, req->tc.size);
	if (out)
		sgs[out_sgs++] = chan->sg;

	in = pack_sg_list(chan->sg, out,
			  VIRTQUEUE_NUM, req->rc.sdata, req->rc.capacity);
	if (in)
		sgs[out_sgs + in_sgs++] = chan->sg + out;

	err = virtqueue_add_sgs(chan->vq, sgs, out_sgs, in_sgs, req,
				GFP_ATOMIC);
	if (err < 0) {
		if (err == -ENOSPC) {
			chan->ring_bufs_avail = 0;
			spin_unlock_irqrestore(&chan->lock, flags);
			err = wait_event_killable(*chan->vc_wq,
						  chan->ring_bufs_avail);
			if (err  == -ERESTARTSYS)
				return err;

			p9_debug(P9_DEBUG_TRANS, "Retry virtio request\n");
			goto req_retry;
		} else {
			spin_unlock_irqrestore(&chan->lock, flags);
			p9_debug(P9_DEBUG_TRANS,
				 "virtio rpc add_sgs returned failure\n");
			return -EIO;
		}
	}
	virtqueue_kick(chan->vq);
	spin_unlock_irqrestore(&chan->lock, flags);

	p9_debug(P9_DEBUG_TRANS, "virtio request kicked\n");
	return 0;
}