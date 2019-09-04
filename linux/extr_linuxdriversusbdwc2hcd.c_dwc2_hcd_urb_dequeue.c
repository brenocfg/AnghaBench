#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct dwc2_qtd {scalar_t__ in_process; struct dwc2_qh* qh; } ;
struct dwc2_qh {int /*<<< orphan*/  qtd_list; int /*<<< orphan*/ * channel; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_desc_enable; } ;
struct TYPE_4__ {scalar_t__ port_connect_status; } ;
struct TYPE_5__ {TYPE_1__ b; } ;
struct dwc2_hsotg {TYPE_3__ params; TYPE_2__ flags; int /*<<< orphan*/  dev; } ;
struct dwc2_hcd_urb {int /*<<< orphan*/ * priv; struct dwc2_qtd* qtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_HC_XFER_URB_DEQUEUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_dump_channel_info (struct dwc2_hsotg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_hc_halt (struct dwc2_hsotg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hcd_qh_deactivate (struct dwc2_hsotg*,struct dwc2_qh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hcd_qh_unlink (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_hcd_qtd_unlink_and_free (struct dwc2_hsotg*,struct dwc2_qtd*,struct dwc2_qh*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dwc2_hcd_urb_dequeue(struct dwc2_hsotg *hsotg,
				struct dwc2_hcd_urb *urb)
{
	struct dwc2_qh *qh;
	struct dwc2_qtd *urb_qtd;

	urb_qtd = urb->qtd;
	if (!urb_qtd) {
		dev_dbg(hsotg->dev, "## Urb QTD is NULL ##\n");
		return -EINVAL;
	}

	qh = urb_qtd->qh;
	if (!qh) {
		dev_dbg(hsotg->dev, "## Urb QTD QH is NULL ##\n");
		return -EINVAL;
	}

	urb->priv = NULL;

	if (urb_qtd->in_process && qh->channel) {
		dwc2_dump_channel_info(hsotg, qh->channel);

		/* The QTD is in process (it has been assigned to a channel) */
		if (hsotg->flags.b.port_connect_status)
			/*
			 * If still connected (i.e. in host mode), halt the
			 * channel so it can be used for other transfers. If
			 * no longer connected, the host registers can't be
			 * written to halt the channel since the core is in
			 * device mode.
			 */
			dwc2_hc_halt(hsotg, qh->channel,
				     DWC2_HC_XFER_URB_DEQUEUE);
	}

	/*
	 * Free the QTD and clean up the associated QH. Leave the QH in the
	 * schedule if it has any remaining QTDs.
	 */
	if (!hsotg->params.dma_desc_enable) {
		u8 in_process = urb_qtd->in_process;

		dwc2_hcd_qtd_unlink_and_free(hsotg, urb_qtd, qh);
		if (in_process) {
			dwc2_hcd_qh_deactivate(hsotg, qh, 0);
			qh->channel = NULL;
		} else if (list_empty(&qh->qtd_list)) {
			dwc2_hcd_qh_unlink(hsotg, qh);
		}
	} else {
		dwc2_hcd_qtd_unlink_and_free(hsotg, urb_qtd, qh);
	}

	return 0;
}