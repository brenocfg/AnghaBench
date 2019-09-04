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
typedef  int u8 ;
struct usb_otg {scalar_t__ state; } ;
struct musb {int is_active; int /*<<< orphan*/  mregs; TYPE_1__* xceiv; int /*<<< orphan*/  controller; } ;
struct TYPE_2__ {struct usb_otg* otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_BDEVICE ; 
 int MUSB_DEVCTL_SESSION ; 
 int /*<<< orphan*/  MUSB_DEV_MODE (struct musb*) ; 
 int /*<<< orphan*/  MUSB_HST_MODE (struct musb*) ; 
 scalar_t__ OTG_STATE_A_IDLE ; 
 scalar_t__ OTG_STATE_A_WAIT_VRISE ; 
 scalar_t__ OTG_STATE_B_IDLE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  otg_set_vbus (struct usb_otg*,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usb_otg_state_string (scalar_t__) ; 

__attribute__((used)) static void omap2430_musb_set_vbus(struct musb *musb, int is_on)
{
	struct usb_otg	*otg = musb->xceiv->otg;
	u8		devctl;
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	/* HDRC controls CPEN, but beware current surges during device
	 * connect.  They can trigger transient overcurrent conditions
	 * that must be ignored.
	 */

	devctl = musb_readb(musb->mregs, MUSB_DEVCTL);

	if (is_on) {
		if (musb->xceiv->otg->state == OTG_STATE_A_IDLE) {
			int loops = 100;
			/* start the session */
			devctl |= MUSB_DEVCTL_SESSION;
			musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);
			/*
			 * Wait for the musb to set as A device to enable the
			 * VBUS
			 */
			while (musb_readb(musb->mregs, MUSB_DEVCTL) &
			       MUSB_DEVCTL_BDEVICE) {

				mdelay(5);
				cpu_relax();

				if (time_after(jiffies, timeout)
				    || loops-- <= 0) {
					dev_err(musb->controller,
					"configured as A device timeout");
					break;
				}
			}

			otg_set_vbus(otg, 1);
		} else {
			musb->is_active = 1;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			devctl |= MUSB_DEVCTL_SESSION;
			MUSB_HST_MODE(musb);
		}
	} else {
		musb->is_active = 0;

		/* NOTE:  we're skipping A_WAIT_VFALL -> A_IDLE and
		 * jumping right to B_IDLE...
		 */

		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		devctl &= ~MUSB_DEVCTL_SESSION;

		MUSB_DEV_MODE(musb);
	}
	musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);

	dev_dbg(musb->controller, "VBUS %s, devctl %02x "
		/* otg %3x conf %08x prcm %08x */ "\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		musb_readb(musb->mregs, MUSB_DEVCTL));
}