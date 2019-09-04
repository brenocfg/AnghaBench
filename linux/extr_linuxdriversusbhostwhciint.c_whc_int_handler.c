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
struct wusbhc {int dummy; } ;
struct whc {int /*<<< orphan*/  dn_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  periodic_list_wq; int /*<<< orphan*/  async_list_wq; TYPE_1__* umc; int /*<<< orphan*/  cmd_wq; scalar_t__ base; } ;
struct usb_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ WUSBSTS ; 
 int WUSBSTS_ASYNC_SCHED_SYNCED ; 
 int WUSBSTS_DNTS_INT ; 
 int WUSBSTS_ERR_INT ; 
 int WUSBSTS_GEN_CMD_DONE ; 
 int WUSBSTS_HOST_ERR ; 
 int WUSBSTS_INT ; 
 int WUSBSTS_INT_MASK ; 
 int WUSBSTS_PERIODIC_SCHED_SYNCED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transfer_done (struct whc*) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

irqreturn_t whc_int_handler(struct usb_hcd *hcd)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);
	u32 sts;

	sts = le_readl(whc->base + WUSBSTS);
	if (!(sts & WUSBSTS_INT_MASK))
		return IRQ_NONE;
	le_writel(sts & WUSBSTS_INT_MASK, whc->base + WUSBSTS);

	if (sts & WUSBSTS_GEN_CMD_DONE)
		wake_up(&whc->cmd_wq);

	if (sts & WUSBSTS_HOST_ERR)
		dev_err(&whc->umc->dev, "FIXME: host system error\n");

	if (sts & WUSBSTS_ASYNC_SCHED_SYNCED)
		wake_up(&whc->async_list_wq);

	if (sts & WUSBSTS_PERIODIC_SCHED_SYNCED)
		wake_up(&whc->periodic_list_wq);

	if (sts & WUSBSTS_DNTS_INT)
		queue_work(whc->workqueue, &whc->dn_work);

	/*
	 * A transfer completed (see [WHCI] section 4.7.1.2 for when
	 * this occurs).
	 */
	if (sts & (WUSBSTS_INT | WUSBSTS_ERR_INT))
		transfer_done(whc);

	return IRQ_HANDLED;
}