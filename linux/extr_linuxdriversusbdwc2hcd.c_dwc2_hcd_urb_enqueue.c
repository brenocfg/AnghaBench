#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct dwc2_qtd {TYPE_5__* urb; TYPE_4__* qh; } ;
struct dwc2_qh {int dummy; } ;
struct TYPE_8__ {scalar_t__ fs_phy_type; scalar_t__ hs_phy_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  port_connect_status; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_3__ hw_params; TYPE_2__ flags; } ;
struct dwc2_hcd_urb {int /*<<< orphan*/  priv; } ;
typedef  enum dwc2_transaction_type { ____Placeholder_dwc2_transaction_type } dwc2_transaction_type ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {scalar_t__ ep_type; } ;

/* Variables and functions */
 int DWC2_TRANSACTION_NONE ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ GHWCFG2_FS_PHY_TYPE_DEDICATED ; 
 scalar_t__ GHWCFG2_HS_PHY_TYPE_UTMI ; 
 int /*<<< orphan*/  GINTMSK ; 
 scalar_t__ GINTSTS_SOF ; 
 int /*<<< orphan*/  HPRT0 ; 
 scalar_t__ HPRT0_SPD_FULL_SPEED ; 
 scalar_t__ HPRT0_SPD_MASK ; 
 scalar_t__ HPRT0_SPD_SHIFT ; 
 int URB_GIVEBACK_ASAP ; 
 scalar_t__ USB_ENDPOINT_XFER_BULK ; 
 int USB_SPEED_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int dwc2_hcd_qtd_add (struct dwc2_hsotg*,struct dwc2_qtd*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_hcd_qtd_init (struct dwc2_qtd*,struct dwc2_hcd_urb*) ; 
 int /*<<< orphan*/  dwc2_hcd_queue_transactions (struct dwc2_hsotg*,int) ; 
 int dwc2_hcd_select_transactions (struct dwc2_hsotg*) ; 
 int dwc2_host_get_speed (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 scalar_t__ dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_hcd_urb_enqueue(struct dwc2_hsotg *hsotg,
				struct dwc2_hcd_urb *urb, struct dwc2_qh *qh,
				struct dwc2_qtd *qtd)
{
	u32 intr_mask;
	int retval;
	int dev_speed;

	if (!hsotg->flags.b.port_connect_status) {
		/* No longer connected */
		dev_err(hsotg->dev, "Not connected\n");
		return -ENODEV;
	}

	dev_speed = dwc2_host_get_speed(hsotg, urb->priv);

	/* Some configurations cannot support LS traffic on a FS root port */
	if ((dev_speed == USB_SPEED_LOW) &&
	    (hsotg->hw_params.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED) &&
	    (hsotg->hw_params.hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI)) {
		u32 hprt0 = dwc2_readl(hsotg, HPRT0);
		u32 prtspd = (hprt0 & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;

		if (prtspd == HPRT0_SPD_FULL_SPEED)
			return -ENODEV;
	}

	if (!qtd)
		return -EINVAL;

	dwc2_hcd_qtd_init(qtd, urb);
	retval = dwc2_hcd_qtd_add(hsotg, qtd, qh);
	if (retval) {
		dev_err(hsotg->dev,
			"DWC OTG HCD URB Enqueue failed adding QTD. Error status %d\n",
			retval);
		return retval;
	}

	intr_mask = dwc2_readl(hsotg, GINTMSK);
	if (!(intr_mask & GINTSTS_SOF)) {
		enum dwc2_transaction_type tr_type;

		if (qtd->qh->ep_type == USB_ENDPOINT_XFER_BULK &&
		    !(qtd->urb->flags & URB_GIVEBACK_ASAP))
			/*
			 * Do not schedule SG transactions until qtd has
			 * URB_GIVEBACK_ASAP set
			 */
			return 0;

		tr_type = dwc2_hcd_select_transactions(hsotg);
		if (tr_type != DWC2_TRANSACTION_NONE)
			dwc2_hcd_queue_transactions(hsotg, tr_type);
	}

	return 0;
}