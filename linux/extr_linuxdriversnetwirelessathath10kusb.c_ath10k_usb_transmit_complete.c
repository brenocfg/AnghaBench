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
struct urb {int /*<<< orphan*/  status; struct ath10k_urb_context* context; } ;
struct sk_buff {int dummy; } ;
struct ath10k_usb_pipe {int /*<<< orphan*/  io_complete_work; int /*<<< orphan*/  io_comp_queue; int /*<<< orphan*/  logical_pipe_num; TYPE_1__* ar_usb; } ;
struct ath10k_urb_context {struct ath10k_usb_pipe* pipe; struct sk_buff* skb; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {struct ath10k* ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_USB_BULK ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_usb_free_urb_to_pipe (struct ath10k_usb_pipe*,struct ath10k_urb_context*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void ath10k_usb_transmit_complete(struct urb *urb)
{
	struct ath10k_urb_context *urb_context = urb->context;
	struct ath10k_usb_pipe *pipe = urb_context->pipe;
	struct ath10k *ar = pipe->ar_usb->ar;
	struct sk_buff *skb;

	if (urb->status != 0) {
		ath10k_dbg(ar, ATH10K_DBG_USB_BULK,
			   "pipe: %d, failed:%d\n",
			   pipe->logical_pipe_num, urb->status);
	}

	skb = urb_context->skb;
	urb_context->skb = NULL;
	ath10k_usb_free_urb_to_pipe(urb_context->pipe, urb_context);

	/* note: queue implements a lock */
	skb_queue_tail(&pipe->io_comp_queue, skb);
	schedule_work(&pipe->io_complete_work);
}