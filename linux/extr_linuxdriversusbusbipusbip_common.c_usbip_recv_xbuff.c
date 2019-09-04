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
struct usbip_device {scalar_t__ side; int /*<<< orphan*/  tcp_socket; } ;
struct urb {int transfer_buffer_length; int actual_length; TYPE_1__* dev; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  SDEV_EVENT_ERROR_TCP ; 
 scalar_t__ USBIP_STUB ; 
 scalar_t__ USBIP_VUDC ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_TCP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_event_add (struct usbip_device*,int /*<<< orphan*/ ) ; 
 int usbip_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int usbip_recv_xbuff(struct usbip_device *ud, struct urb *urb)
{
	int ret;
	int size;

	if (ud->side == USBIP_STUB || ud->side == USBIP_VUDC) {
		/* the direction of urb must be OUT. */
		if (usb_pipein(urb->pipe))
			return 0;

		size = urb->transfer_buffer_length;
	} else {
		/* the direction of urb must be IN. */
		if (usb_pipeout(urb->pipe))
			return 0;

		size = urb->actual_length;
	}

	/* no need to recv xbuff */
	if (!(size > 0))
		return 0;

	if (size > urb->transfer_buffer_length) {
		/* should not happen, probably malicious packet */
		if (ud->side == USBIP_STUB) {
			usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
			return 0;
		} else {
			usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
			return -EPIPE;
		}
	}

	ret = usbip_recv(ud->tcp_socket, urb->transfer_buffer, size);
	if (ret != size) {
		dev_err(&urb->dev->dev, "recv xbuf, %d\n", ret);
		if (ud->side == USBIP_STUB || ud->side == USBIP_VUDC) {
			usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		} else {
			usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
			return -EPIPE;
		}
	}

	return ret;
}