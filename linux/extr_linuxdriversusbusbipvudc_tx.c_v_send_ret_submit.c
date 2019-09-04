#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tcp_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct vudc {TYPE_4__ ud; TYPE_1__ gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqnum; } ;
struct usbip_iso_packet_descriptor {int iov_len; struct usbip_iso_packet_descriptor* iov_base; TYPE_2__ base; } ;
struct usbip_header {int iov_len; struct usbip_header* iov_base; TYPE_2__ base; } ;
struct urbp {scalar_t__ type; struct urb* urb; } ;
struct urb {int actual_length; int number_of_packets; TYPE_3__* iso_frame_desc; struct usbip_iso_packet_descriptor* transfer_buffer; int /*<<< orphan*/  pipe; } ;
struct msghdr {int iov_len; struct msghdr* iov_base; TYPE_2__ base; } ;
struct kvec {int iov_len; struct kvec* iov_base; TYPE_2__ base; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pdu_header ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_7__ {int offset; int actual_length; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  VUDC_EVENT_ERROR_MALLOC ; 
 int /*<<< orphan*/  VUDC_EVENT_ERROR_TCP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_urbp_and_urb (struct urbp*) ; 
 struct usbip_iso_packet_descriptor* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct usbip_iso_packet_descriptor*,struct usbip_iso_packet_descriptor*,int,size_t) ; 
 int /*<<< orphan*/  kfree (struct usbip_iso_packet_descriptor*) ; 
 int /*<<< orphan*/  memset (struct usbip_iso_packet_descriptor*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_ret_submit_pdu (struct usbip_iso_packet_descriptor*,struct urbp*) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 struct usbip_iso_packet_descriptor* usbip_alloc_iso_desc_pdu (struct urb*,int*) ; 
 int /*<<< orphan*/  usbip_dbg_stub_tx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_header_correct_endian (struct usbip_iso_packet_descriptor*,int) ; 

__attribute__((used)) static int v_send_ret_submit(struct vudc *udc, struct urbp *urb_p)
{
	struct urb *urb = urb_p->urb;
	struct usbip_header pdu_header;
	struct usbip_iso_packet_descriptor *iso_buffer = NULL;
	struct kvec *iov = NULL;
	int iovnum = 0;
	int ret = 0;
	size_t txsize;
	struct msghdr msg;

	txsize = 0;
	memset(&pdu_header, 0, sizeof(pdu_header));
	memset(&msg, 0, sizeof(msg));

	if (urb->actual_length > 0 && !urb->transfer_buffer) {
		dev_err(&udc->gadget.dev,
			"urb: actual_length %d transfer_buffer null\n",
			urb->actual_length);
		return -1;
	}

	if (urb_p->type == USB_ENDPOINT_XFER_ISOC)
		iovnum = 2 + urb->number_of_packets;
	else
		iovnum = 2;

	iov = kcalloc(iovnum, sizeof(*iov), GFP_KERNEL);
	if (!iov) {
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_MALLOC);
		ret = -ENOMEM;
		goto out;
	}
	iovnum = 0;

	/* 1. setup usbip_header */
	setup_ret_submit_pdu(&pdu_header, urb_p);
	usbip_dbg_stub_tx("setup txdata seqnum: %d\n",
			  pdu_header.base.seqnum);
	usbip_header_correct_endian(&pdu_header, 1);

	iov[iovnum].iov_base = &pdu_header;
	iov[iovnum].iov_len  = sizeof(pdu_header);
	iovnum++;
	txsize += sizeof(pdu_header);

	/* 2. setup transfer buffer */
	if (urb_p->type != USB_ENDPOINT_XFER_ISOC &&
	    usb_pipein(urb->pipe) && urb->actual_length > 0) {
		iov[iovnum].iov_base = urb->transfer_buffer;
		iov[iovnum].iov_len  = urb->actual_length;
		iovnum++;
		txsize += urb->actual_length;
	} else if (urb_p->type == USB_ENDPOINT_XFER_ISOC &&
		usb_pipein(urb->pipe)) {
		/* FIXME - copypasted from stub_tx, refactor */
		int i;

		for (i = 0; i < urb->number_of_packets; i++) {
			iov[iovnum].iov_base = urb->transfer_buffer +
				urb->iso_frame_desc[i].offset;
			iov[iovnum].iov_len =
				urb->iso_frame_desc[i].actual_length;
			iovnum++;
			txsize += urb->iso_frame_desc[i].actual_length;
		}

		if (txsize != sizeof(pdu_header) + urb->actual_length) {
			usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
			ret = -EPIPE;
			goto out;
		}
	}
	/* else - no buffer to send */

	/* 3. setup iso_packet_descriptor */
	if (urb_p->type == USB_ENDPOINT_XFER_ISOC) {
		ssize_t len = 0;

		iso_buffer = usbip_alloc_iso_desc_pdu(urb, &len);
		if (!iso_buffer) {
			usbip_event_add(&udc->ud,
					VUDC_EVENT_ERROR_MALLOC);
			ret = -ENOMEM;
			goto out;
		}

		iov[iovnum].iov_base = iso_buffer;
		iov[iovnum].iov_len  = len;
		txsize += len;
		iovnum++;
	}

	ret = kernel_sendmsg(udc->ud.tcp_socket, &msg,
						iov,  iovnum, txsize);
	if (ret != txsize) {
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
		if (ret >= 0)
			ret = -EPIPE;
		goto out;
	}

out:
	kfree(iov);
	kfree(iso_buffer);
	free_urbp_and_urb(urb_p);
	if (ret < 0)
		return ret;
	return txsize;
}