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
struct usbhsh_request {struct urb* urb; } ;
struct usbhs_pkt {int /*<<< orphan*/  dma; } ;
struct urb {int /*<<< orphan*/  transfer_dma; scalar_t__ num_sgs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct usbhsh_request* usbhsh_pkt_to_ureq (struct usbhs_pkt*) ; 

__attribute__((used)) static int usbhsh_dma_map_ctrl(struct device *dma_dev, struct usbhs_pkt *pkt,
			       int map)
{
	if (map) {
		struct usbhsh_request *ureq = usbhsh_pkt_to_ureq(pkt);
		struct urb *urb = ureq->urb;

		/* it can not use scatter/gather */
		if (urb->num_sgs)
			return -EINVAL;

		pkt->dma = urb->transfer_dma;
		if (!pkt->dma)
			return -EINVAL;
	}

	return 0;
}