#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct urb {int /*<<< orphan*/  pipe; } ;
struct isp1760_qh {int slot; } ;
struct isp1760_hcd {TYPE_2__* int_slots; TYPE_1__* atl_slots; } ;
struct TYPE_4__ {int /*<<< orphan*/ * qtd; int /*<<< orphan*/ * qh; } ;
struct TYPE_3__ {int /*<<< orphan*/ * qtd; int /*<<< orphan*/ * qh; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_ATL_PTD_SKIPMAP_REG ; 
 int /*<<< orphan*/  HC_INT_PTD_SKIPMAP_REG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usb_pipebulk (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipecontrol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kill_transfer(struct usb_hcd *hcd, struct urb *urb,
		struct isp1760_qh *qh)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	int skip_map;

	WARN_ON(qh->slot == -1);

	/* We need to forcefully reclaim the slot since some transfers never
	   return, e.g. interrupt transfers and NAKed bulk transfers. */
	if (usb_pipecontrol(urb->pipe) || usb_pipebulk(urb->pipe)) {
		skip_map = reg_read32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG);
		skip_map |= (1 << qh->slot);
		reg_write32(hcd->regs, HC_ATL_PTD_SKIPMAP_REG, skip_map);
		priv->atl_slots[qh->slot].qh = NULL;
		priv->atl_slots[qh->slot].qtd = NULL;
	} else {
		skip_map = reg_read32(hcd->regs, HC_INT_PTD_SKIPMAP_REG);
		skip_map |= (1 << qh->slot);
		reg_write32(hcd->regs, HC_INT_PTD_SKIPMAP_REG, skip_map);
		priv->int_slots[qh->slot].qh = NULL;
		priv->int_slots[qh->slot].qtd = NULL;
	}

	qh->slot = -1;
}