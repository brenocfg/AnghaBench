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
struct urb {int dummy; } ;
struct ath6kl_usb_pipe {int /*<<< orphan*/  urb_submitted; int /*<<< orphan*/  ep_address; int /*<<< orphan*/  usb_pipe_handle; int /*<<< orphan*/  logical_pipe_num; TYPE_1__* ar_usb; } ;
struct ath6kl_urb_context {TYPE_2__* skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_USB_BULK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 struct ath6kl_urb_context* ath6kl_usb_alloc_urb_from_pipe (struct ath6kl_usb_pipe*) ; 
 int /*<<< orphan*/  ath6kl_usb_cleanup_recv_urb (struct ath6kl_urb_context*) ; 
 int /*<<< orphan*/  ath6kl_usb_recv_complete ; 
 TYPE_2__* dev_alloc_skb (int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ath6kl_urb_context*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void ath6kl_usb_post_recv_transfers(struct ath6kl_usb_pipe *recv_pipe,
					   int buffer_length)
{
	struct ath6kl_urb_context *urb_context;
	struct urb *urb;
	int usb_status;

	while (true) {
		urb_context = ath6kl_usb_alloc_urb_from_pipe(recv_pipe);
		if (urb_context == NULL)
			break;

		urb_context->skb = dev_alloc_skb(buffer_length);
		if (urb_context->skb == NULL)
			goto err_cleanup_urb;

		urb = usb_alloc_urb(0, GFP_ATOMIC);
		if (urb == NULL)
			goto err_cleanup_urb;

		usb_fill_bulk_urb(urb,
				  recv_pipe->ar_usb->udev,
				  recv_pipe->usb_pipe_handle,
				  urb_context->skb->data,
				  buffer_length,
				  ath6kl_usb_recv_complete, urb_context);

		ath6kl_dbg(ATH6KL_DBG_USB_BULK,
			   "ath6kl usb: bulk recv submit:%d, 0x%X (ep:0x%2.2X), %d bytes buf:0x%p\n",
			   recv_pipe->logical_pipe_num,
			   recv_pipe->usb_pipe_handle, recv_pipe->ep_address,
			   buffer_length, urb_context->skb);

		usb_anchor_urb(urb, &recv_pipe->urb_submitted);
		usb_status = usb_submit_urb(urb, GFP_ATOMIC);

		if (usb_status) {
			ath6kl_dbg(ATH6KL_DBG_USB_BULK,
				   "ath6kl usb : usb bulk recv failed %d\n",
				   usb_status);
			usb_unanchor_urb(urb);
			usb_free_urb(urb);
			goto err_cleanup_urb;
		}
		usb_free_urb(urb);
	}
	return;

err_cleanup_urb:
	ath6kl_usb_cleanup_recv_urb(urb_context);
	return;
}