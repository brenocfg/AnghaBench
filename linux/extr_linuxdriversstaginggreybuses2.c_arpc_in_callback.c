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
struct urb {int actual_length; struct arpc_response_message* transfer_buffer; TYPE_1__* dev; struct es2_ap_dev* context; } ;
struct es2_ap_dev {int /*<<< orphan*/  arpc_lock; } ;
struct device {int dummy; } ;
struct arpc_response_message {int /*<<< orphan*/  id; } ;
struct arpc {int /*<<< orphan*/  response_received; int /*<<< orphan*/  resp; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 int EPROTO ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  arpc_del (struct es2_ap_dev*,struct arpc*) ; 
 struct arpc* arpc_find (struct es2_ap_dev*,int /*<<< orphan*/ ) ; 
 int check_urb_status (struct urb*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct arpc_response_message*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arpc_in_callback(struct urb *urb)
{
	struct es2_ap_dev *es2 = urb->context;
	struct device *dev = &urb->dev->dev;
	int status = check_urb_status(urb);
	struct arpc *rpc;
	struct arpc_response_message *resp;
	unsigned long flags;
	int retval;

	if (status) {
		if ((status == -EAGAIN) || (status == -EPROTO))
			goto exit;

		/* The urb is being unlinked */
		if (status == -ENOENT || status == -ESHUTDOWN)
			return;

		dev_err(dev, "arpc in-urb error %d (dropped)\n", status);
		return;
	}

	if (urb->actual_length < sizeof(*resp)) {
		dev_err(dev, "short aprc response received\n");
		goto exit;
	}

	resp = urb->transfer_buffer;
	spin_lock_irqsave(&es2->arpc_lock, flags);
	rpc = arpc_find(es2, resp->id);
	if (!rpc) {
		dev_err(dev, "invalid arpc response id received: %u\n",
			le16_to_cpu(resp->id));
		spin_unlock_irqrestore(&es2->arpc_lock, flags);
		goto exit;
	}

	arpc_del(es2, rpc);
	memcpy(rpc->resp, resp, sizeof(*resp));
	complete(&rpc->response_received);
	spin_unlock_irqrestore(&es2->arpc_lock, flags);

exit:
	/* put our urb back in the request pool */
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval)
		dev_err(dev, "failed to resubmit arpc in-urb: %d\n", retval);
}