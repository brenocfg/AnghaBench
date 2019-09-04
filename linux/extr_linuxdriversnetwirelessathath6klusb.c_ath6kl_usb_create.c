#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct ath6kl_usb_pipe {int /*<<< orphan*/  io_comp_queue; int /*<<< orphan*/  io_complete_work; } ;
struct ath6kl_usb {int /*<<< orphan*/ * diag_resp_buffer; int /*<<< orphan*/ * diag_cmd_buffer; struct ath6kl_usb_pipe* pipes; struct usb_interface* interface; struct usb_device* udev; int /*<<< orphan*/  cs_lock; } ;

/* Variables and functions */
 int ATH6KL_USB_MAX_DIAG_CMD ; 
 int ATH6KL_USB_MAX_DIAG_RESP ; 
 int ATH6KL_USB_PIPE_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_usb_destroy (struct ath6kl_usb*) ; 
 int /*<<< orphan*/  ath6kl_usb_io_comp_work ; 
 int ath6kl_usb_setup_pipe_resources (struct ath6kl_usb*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ath6kl_usb*) ; 

__attribute__((used)) static struct ath6kl_usb *ath6kl_usb_create(struct usb_interface *interface)
{
	struct usb_device *dev = interface_to_usbdev(interface);
	struct ath6kl_usb *ar_usb;
	struct ath6kl_usb_pipe *pipe;
	int status = 0;
	int i;

	ar_usb = kzalloc(sizeof(struct ath6kl_usb), GFP_KERNEL);
	if (ar_usb == NULL)
		goto fail_ath6kl_usb_create;

	usb_set_intfdata(interface, ar_usb);
	spin_lock_init(&(ar_usb->cs_lock));
	ar_usb->udev = dev;
	ar_usb->interface = interface;

	for (i = 0; i < ATH6KL_USB_PIPE_MAX; i++) {
		pipe = &ar_usb->pipes[i];
		INIT_WORK(&pipe->io_complete_work,
			  ath6kl_usb_io_comp_work);
		skb_queue_head_init(&pipe->io_comp_queue);
	}

	ar_usb->diag_cmd_buffer = kzalloc(ATH6KL_USB_MAX_DIAG_CMD, GFP_KERNEL);
	if (ar_usb->diag_cmd_buffer == NULL) {
		status = -ENOMEM;
		goto fail_ath6kl_usb_create;
	}

	ar_usb->diag_resp_buffer = kzalloc(ATH6KL_USB_MAX_DIAG_RESP,
					   GFP_KERNEL);
	if (ar_usb->diag_resp_buffer == NULL) {
		status = -ENOMEM;
		goto fail_ath6kl_usb_create;
	}

	status = ath6kl_usb_setup_pipe_resources(ar_usb);

fail_ath6kl_usb_create:
	if (status != 0) {
		ath6kl_usb_destroy(ar_usb);
		ar_usb = NULL;
	}
	return ar_usb;
}