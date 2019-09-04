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
typedef  int u32 ;
struct usb_request {int length; int /*<<< orphan*/  actual; } ;
struct renesas_usb3_request {struct usb_request req; } ;
struct renesas_usb3_prd {int word1; } ;
struct renesas_usb3_ep {TYPE_1__* dma; } ;
struct TYPE_2__ {struct renesas_usb3_prd* prd; } ;

/* Variables and functions */
 int EIO ; 
 int USB3_DMA_MAX_XFER_SIZE ; 
 int USB3_DMA_NUM_PRD_ENTRIES ; 
 int USB3_PRD1_D ; 
 int USB3_PRD1_E ; 
 int USB3_PRD1_SIZE_MASK ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static int usb3_dma_update_status(struct renesas_usb3_ep *usb3_ep,
				  struct renesas_usb3_request *usb3_req)
{
	struct renesas_usb3_prd *cur_prd = usb3_ep->dma->prd;
	struct usb_request *req = &usb3_req->req;
	u32 remain, len;
	int i = 0;
	int status = 0;

	rmb();	/* The controller updated prd entries */

	do {
		if (cur_prd->word1 & USB3_PRD1_D)
			status = -EIO;
		if (cur_prd->word1 & USB3_PRD1_E)
			len = req->length % USB3_DMA_MAX_XFER_SIZE;
		else
			len = USB3_DMA_MAX_XFER_SIZE;
		remain = cur_prd->word1 & USB3_PRD1_SIZE_MASK;
		req->actual += len - remain;

		if (cur_prd->word1 & USB3_PRD1_E ||
		    (i + 1) < USB3_DMA_NUM_PRD_ENTRIES)
			break;

		cur_prd++;
		i++;
	} while (1);

	return status;
}