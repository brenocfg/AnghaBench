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
typedef  int /*<<< orphan*/  u32 ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {int ep_type; int /*<<< orphan*/  hc_num; int /*<<< orphan*/  ep_is_in; int /*<<< orphan*/  complete_split; int /*<<< orphan*/  do_split; int /*<<< orphan*/  error_state; int /*<<< orphan*/  do_ping; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCINTMSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCINTMSK_ACK ; 
 int /*<<< orphan*/  HCINTMSK_BBLERR ; 
 int /*<<< orphan*/  HCINTMSK_CHHLTD ; 
 int /*<<< orphan*/  HCINTMSK_DATATGLERR ; 
 int /*<<< orphan*/  HCINTMSK_FRMOVRUN ; 
 int /*<<< orphan*/  HCINTMSK_NAK ; 
 int /*<<< orphan*/  HCINTMSK_NYET ; 
 int /*<<< orphan*/  HCINTMSK_STALL ; 
 int /*<<< orphan*/  HCINTMSK_XACTERR ; 
 int /*<<< orphan*/  HCINTMSK_XFERCOMPL ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dbg_perio () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hc_enable_slave_ints(struct dwc2_hsotg *hsotg,
				      struct dwc2_host_chan *chan)
{
	u32 hcintmsk = HCINTMSK_CHHLTD;

	switch (chan->ep_type) {
	case USB_ENDPOINT_XFER_CONTROL:
	case USB_ENDPOINT_XFER_BULK:
		dev_vdbg(hsotg->dev, "control/bulk\n");
		hcintmsk |= HCINTMSK_XFERCOMPL;
		hcintmsk |= HCINTMSK_STALL;
		hcintmsk |= HCINTMSK_XACTERR;
		hcintmsk |= HCINTMSK_DATATGLERR;
		if (chan->ep_is_in) {
			hcintmsk |= HCINTMSK_BBLERR;
		} else {
			hcintmsk |= HCINTMSK_NAK;
			hcintmsk |= HCINTMSK_NYET;
			if (chan->do_ping)
				hcintmsk |= HCINTMSK_ACK;
		}

		if (chan->do_split) {
			hcintmsk |= HCINTMSK_NAK;
			if (chan->complete_split)
				hcintmsk |= HCINTMSK_NYET;
			else
				hcintmsk |= HCINTMSK_ACK;
		}

		if (chan->error_state)
			hcintmsk |= HCINTMSK_ACK;
		break;

	case USB_ENDPOINT_XFER_INT:
		if (dbg_perio())
			dev_vdbg(hsotg->dev, "intr\n");
		hcintmsk |= HCINTMSK_XFERCOMPL;
		hcintmsk |= HCINTMSK_NAK;
		hcintmsk |= HCINTMSK_STALL;
		hcintmsk |= HCINTMSK_XACTERR;
		hcintmsk |= HCINTMSK_DATATGLERR;
		hcintmsk |= HCINTMSK_FRMOVRUN;

		if (chan->ep_is_in)
			hcintmsk |= HCINTMSK_BBLERR;
		if (chan->error_state)
			hcintmsk |= HCINTMSK_ACK;
		if (chan->do_split) {
			if (chan->complete_split)
				hcintmsk |= HCINTMSK_NYET;
			else
				hcintmsk |= HCINTMSK_ACK;
		}
		break;

	case USB_ENDPOINT_XFER_ISOC:
		if (dbg_perio())
			dev_vdbg(hsotg->dev, "isoc\n");
		hcintmsk |= HCINTMSK_XFERCOMPL;
		hcintmsk |= HCINTMSK_FRMOVRUN;
		hcintmsk |= HCINTMSK_ACK;

		if (chan->ep_is_in) {
			hcintmsk |= HCINTMSK_XACTERR;
			hcintmsk |= HCINTMSK_BBLERR;
		}
		break;
	default:
		dev_err(hsotg->dev, "## Unknown EP type ##\n");
		break;
	}

	dwc2_writel(hsotg, hcintmsk, HCINTMSK(chan->hc_num));
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HCINTMSK to %08x\n", hcintmsk);
}