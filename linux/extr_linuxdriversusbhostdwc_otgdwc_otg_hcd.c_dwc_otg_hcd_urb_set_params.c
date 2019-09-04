#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  interval; void* flags; void* setup_dma; void* setup_packet; void* length; void* dma; void* buf; void* priv; } ;
typedef  TYPE_1__ dwc_otg_hcd_urb_t ;
typedef  void* dwc_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_E_IN_PROGRESS ; 

void dwc_otg_hcd_urb_set_params(dwc_otg_hcd_urb_t * dwc_otg_urb,
				void *urb_handle, void *buf, dwc_dma_t dma,
				uint32_t buflen, void *setup_packet,
				dwc_dma_t setup_dma, uint32_t flags,
				uint16_t interval)
{
	dwc_otg_urb->priv = urb_handle;
	dwc_otg_urb->buf = buf;
	dwc_otg_urb->dma = dma;
	dwc_otg_urb->length = buflen;
	dwc_otg_urb->setup_packet = setup_packet;
	dwc_otg_urb->setup_dma = setup_dma;
	dwc_otg_urb->flags = flags;
	dwc_otg_urb->interval = interval;
	dwc_otg_urb->status = -DWC_E_IN_PROGRESS;
}