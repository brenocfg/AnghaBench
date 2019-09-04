#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  seqnum; } ;
struct TYPE_11__ {scalar_t__ transfer_buffer_length; int /*<<< orphan*/  setup; int /*<<< orphan*/  number_of_packets; } ;
struct TYPE_12__ {TYPE_1__ cmd_submit; } ;
struct usbip_header {TYPE_3__ base; TYPE_2__ u; } ;
struct usbip_device {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct stub_priv {TYPE_4__* urb; } ;
struct stub_device {struct usb_device* udev; struct usbip_device ud; } ;
struct TYPE_14__ {int pipe; int /*<<< orphan*/  complete; struct usb_device* dev; void* context; int /*<<< orphan*/  setup_packet; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SDEV_EVENT_ERROR_MALLOC ; 
 int /*<<< orphan*/  SDEV_EVENT_ERROR_SUBMIT ; 
 int /*<<< orphan*/  USBIP_CMD_SUBMIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int get_pipe (struct stub_device*,struct usbip_header*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  masking_bogus_flags (TYPE_4__*) ; 
 int /*<<< orphan*/  stub_complete ; 
 struct stub_priv* stub_priv_alloc (struct stub_device*,struct usbip_header*) ; 
 int /*<<< orphan*/  tweak_special_requests (TYPE_4__*) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeisoc (int) ; 
 int usb_submit_urb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_stub_rx (char*,...) ; 
 int /*<<< orphan*/  usbip_dump_header (struct usbip_header*) ; 
 int /*<<< orphan*/  usbip_dump_urb (TYPE_4__*) ; 
 int /*<<< orphan*/  usbip_event_add (struct usbip_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_pack_pdu (struct usbip_header*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbip_recv_iso (struct usbip_device*,TYPE_4__*) ; 
 scalar_t__ usbip_recv_xbuff (struct usbip_device*,TYPE_4__*) ; 

__attribute__((used)) static void stub_recv_cmd_submit(struct stub_device *sdev,
				 struct usbip_header *pdu)
{
	int ret;
	struct stub_priv *priv;
	struct usbip_device *ud = &sdev->ud;
	struct usb_device *udev = sdev->udev;
	int pipe = get_pipe(sdev, pdu);

	if (pipe == -1)
		return;

	priv = stub_priv_alloc(sdev, pdu);
	if (!priv)
		return;

	/* setup a urb */
	if (usb_pipeisoc(pipe))
		priv->urb = usb_alloc_urb(pdu->u.cmd_submit.number_of_packets,
					  GFP_KERNEL);
	else
		priv->urb = usb_alloc_urb(0, GFP_KERNEL);

	if (!priv->urb) {
		usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
		return;
	}

	/* allocate urb transfer buffer, if needed */
	if (pdu->u.cmd_submit.transfer_buffer_length > 0) {
		priv->urb->transfer_buffer =
			kzalloc(pdu->u.cmd_submit.transfer_buffer_length,
				GFP_KERNEL);
		if (!priv->urb->transfer_buffer) {
			usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
			return;
		}
	}

	/* copy urb setup packet */
	priv->urb->setup_packet = kmemdup(&pdu->u.cmd_submit.setup, 8,
					  GFP_KERNEL);
	if (!priv->urb->setup_packet) {
		dev_err(&udev->dev, "allocate setup_packet\n");
		usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
		return;
	}

	/* set other members from the base header of pdu */
	priv->urb->context                = (void *) priv;
	priv->urb->dev                    = udev;
	priv->urb->pipe                   = pipe;
	priv->urb->complete               = stub_complete;

	usbip_pack_pdu(pdu, priv->urb, USBIP_CMD_SUBMIT, 0);


	if (usbip_recv_xbuff(ud, priv->urb) < 0)
		return;

	if (usbip_recv_iso(ud, priv->urb) < 0)
		return;

	/* no need to submit an intercepted request, but harmless? */
	tweak_special_requests(priv->urb);

	masking_bogus_flags(priv->urb);
	/* urb is now ready to submit */
	ret = usb_submit_urb(priv->urb, GFP_KERNEL);

	if (ret == 0)
		usbip_dbg_stub_rx("submit urb ok, seqnum %u\n",
				  pdu->base.seqnum);
	else {
		dev_err(&udev->dev, "submit_urb error, %d\n", ret);
		usbip_dump_header(pdu);
		usbip_dump_urb(priv->urb);

		/*
		 * Pessimistic.
		 * This connection will be discarded.
		 */
		usbip_event_add(ud, SDEV_EVENT_ERROR_SUBMIT);
	}

	usbip_dbg_stub_rx("Leave\n");
}