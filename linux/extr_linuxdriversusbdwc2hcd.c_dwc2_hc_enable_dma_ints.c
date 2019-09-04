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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dma_desc_enable; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
struct dwc2_host_chan {scalar_t__ ep_type; int /*<<< orphan*/  hc_num; scalar_t__ ep_is_in; int /*<<< orphan*/  do_split; scalar_t__ error_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCINTMSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCINTMSK_ACK ; 
 int /*<<< orphan*/  HCINTMSK_AHBERR ; 
 int /*<<< orphan*/  HCINTMSK_CHHLTD ; 
 int /*<<< orphan*/  HCINTMSK_DATATGLERR ; 
 int /*<<< orphan*/  HCINTMSK_NAK ; 
 int /*<<< orphan*/  HCINTMSK_XFERCOMPL ; 
 scalar_t__ USB_ENDPOINT_XFER_INT ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hc_enable_dma_ints(struct dwc2_hsotg *hsotg,
				    struct dwc2_host_chan *chan)
{
	u32 hcintmsk = HCINTMSK_CHHLTD;

	/*
	 * For Descriptor DMA mode core halts the channel on AHB error.
	 * Interrupt is not required.
	 */
	if (!hsotg->params.dma_desc_enable) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA disabled\n");
		hcintmsk |= HCINTMSK_AHBERR;
	} else {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA enabled\n");
		if (chan->ep_type == USB_ENDPOINT_XFER_ISOC)
			hcintmsk |= HCINTMSK_XFERCOMPL;
	}

	if (chan->error_state && !chan->do_split &&
	    chan->ep_type != USB_ENDPOINT_XFER_ISOC) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "setting ACK\n");
		hcintmsk |= HCINTMSK_ACK;
		if (chan->ep_is_in) {
			hcintmsk |= HCINTMSK_DATATGLERR;
			if (chan->ep_type != USB_ENDPOINT_XFER_INT)
				hcintmsk |= HCINTMSK_NAK;
		}
	}

	dwc2_writel(hsotg, hcintmsk, HCINTMSK(chan->hc_num));
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HCINTMSK to %08x\n", hcintmsk);
}