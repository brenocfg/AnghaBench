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
typedef  int u8 ;
struct musb {int is_suspended; TYPE_3__* xceiv; int /*<<< orphan*/  lock; int /*<<< orphan*/  g; TYPE_1__* gadget_driver; int /*<<< orphan*/  mregs; } ;
struct TYPE_6__ {TYPE_2__* otg; } ;
struct TYPE_5__ {int state; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* suspend ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_VBUS ; 
#define  OTG_STATE_B_IDLE 129 
#define  OTG_STATE_B_PERIPHERAL 128 
 int /*<<< orphan*/  WARNING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,int) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

void musb_g_suspend(struct musb *musb)
{
	u8	devctl;

	devctl = musb_readb(musb->mregs, MUSB_DEVCTL);
	musb_dbg(musb, "musb_g_suspend: devctl %02x", devctl);

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_B_IDLE:
		if ((devctl & MUSB_DEVCTL_VBUS) == MUSB_DEVCTL_VBUS)
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		break;
	case OTG_STATE_B_PERIPHERAL:
		musb->is_suspended = 1;
		if (musb->gadget_driver && musb->gadget_driver->suspend) {
			spin_unlock(&musb->lock);
			musb->gadget_driver->suspend(&musb->g);
			spin_lock(&musb->lock);
		}
		break;
	default:
		/* REVISIT if B_HOST, clear DEVCTL.HOSTREQ;
		 * A_PERIPHERAL may need care too
		 */
		WARNING("unhandled SUSPEND transition (%s)",
				usb_otg_state_string(musb->xceiv->otg->state));
	}
}