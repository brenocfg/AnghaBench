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
struct usb_request {int /*<<< orphan*/  dma; int /*<<< orphan*/  num_sgs; } ;
struct usbhsg_request {struct usb_request req; } ;
struct usbhs_pkt {int /*<<< orphan*/  dma; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int usb_gadget_map_request_by_dev (struct device*,struct usb_request*,int) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request_by_dev (struct device*,struct usb_request*,int) ; 
 int usbhs_pipe_is_dir_host (struct usbhs_pipe*) ; 
 struct usbhsg_request* usbhsg_pkt_to_ureq (struct usbhs_pkt*) ; 

__attribute__((used)) static int usbhsg_dma_map_ctrl(struct device *dma_dev, struct usbhs_pkt *pkt,
			       int map)
{
	struct usbhsg_request *ureq = usbhsg_pkt_to_ureq(pkt);
	struct usb_request *req = &ureq->req;
	struct usbhs_pipe *pipe = pkt->pipe;
	enum dma_data_direction dir;
	int ret = 0;

	dir = usbhs_pipe_is_dir_host(pipe);

	if (map) {
		/* it can not use scatter/gather */
		WARN_ON(req->num_sgs);

		ret = usb_gadget_map_request_by_dev(dma_dev, req, dir);
		if (ret < 0)
			return ret;

		pkt->dma = req->dma;
	} else {
		usb_gadget_unmap_request_by_dev(dma_dev, req, dir);
	}

	return ret;
}