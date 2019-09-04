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
struct usb_hcd {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_dump_urb_info(struct usb_hcd *hcd, struct urb *urb,
			       char *fn_name)
{
#ifdef VERBOSE_DEBUG
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	char *pipetype = NULL;
	char *speed = NULL;

	dev_vdbg(hsotg->dev, "%s, urb %p\n", fn_name, urb);
	dev_vdbg(hsotg->dev, "  Device address: %d\n",
		 usb_pipedevice(urb->pipe));
	dev_vdbg(hsotg->dev, "  Endpoint: %d, %s\n",
		 usb_pipeendpoint(urb->pipe),
		 usb_pipein(urb->pipe) ? "IN" : "OUT");

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
		pipetype = "CONTROL";
		break;
	case PIPE_BULK:
		pipetype = "BULK";
		break;
	case PIPE_INTERRUPT:
		pipetype = "INTERRUPT";
		break;
	case PIPE_ISOCHRONOUS:
		pipetype = "ISOCHRONOUS";
		break;
	}

	dev_vdbg(hsotg->dev, "  Endpoint type: %s %s (%s)\n", pipetype,
		 usb_urb_dir_in(urb) ? "IN" : "OUT", usb_pipein(urb->pipe) ?
		 "IN" : "OUT");

	switch (urb->dev->speed) {
	case USB_SPEED_HIGH:
		speed = "HIGH";
		break;
	case USB_SPEED_FULL:
		speed = "FULL";
		break;
	case USB_SPEED_LOW:
		speed = "LOW";
		break;
	default:
		speed = "UNKNOWN";
		break;
	}

	dev_vdbg(hsotg->dev, "  Speed: %s\n", speed);
	dev_vdbg(hsotg->dev, "  Max packet size: %d\n",
		 usb_maxpacket(urb->dev, urb->pipe, usb_pipeout(urb->pipe)));
	dev_vdbg(hsotg->dev, "  Data buffer length: %d\n",
		 urb->transfer_buffer_length);
	dev_vdbg(hsotg->dev, "  Transfer buffer: %p, Transfer DMA: %08lx\n",
		 urb->transfer_buffer, (unsigned long)urb->transfer_dma);
	dev_vdbg(hsotg->dev, "  Setup buffer: %p, Setup DMA: %08lx\n",
		 urb->setup_packet, (unsigned long)urb->setup_dma);
	dev_vdbg(hsotg->dev, "  Interval: %d\n", urb->interval);

	if (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) {
		int i;

		for (i = 0; i < urb->number_of_packets; i++) {
			dev_vdbg(hsotg->dev, "  ISO Desc %d:\n", i);
			dev_vdbg(hsotg->dev, "    offset: %d, length %d\n",
				 urb->iso_frame_desc[i].offset,
				 urb->iso_frame_desc[i].length);
		}
	}
#endif
}