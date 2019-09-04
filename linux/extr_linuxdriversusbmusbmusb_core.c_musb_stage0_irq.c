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
typedef  int u8 ;
struct musb {int /*<<< orphan*/  irq_work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MUSB_INTR_CONNECT ; 
 int MUSB_INTR_DISCONNECT ; 
 int MUSB_INTR_RESET ; 
 int MUSB_INTR_RESUME ; 
 int MUSB_INTR_SESSREQ ; 
 int MUSB_INTR_SUSPEND ; 
 int MUSB_INTR_VBUSERROR ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,int,int) ; 
 int /*<<< orphan*/  musb_handle_intr_connect (struct musb*,int,int) ; 
 int /*<<< orphan*/  musb_handle_intr_disconnect (struct musb*,int) ; 
 int /*<<< orphan*/  musb_handle_intr_reset (struct musb*) ; 
 int /*<<< orphan*/  musb_handle_intr_resume (struct musb*,int) ; 
 scalar_t__ musb_handle_intr_sessreq (struct musb*,int) ; 
 int /*<<< orphan*/  musb_handle_intr_suspend (struct musb*,int) ; 
 int /*<<< orphan*/  musb_handle_intr_vbuserr (struct musb*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t musb_stage0_irq(struct musb *musb, u8 int_usb,
				u8 devctl)
{
	irqreturn_t handled = IRQ_NONE;

	musb_dbg(musb, "<== DevCtl=%02x, int_usb=0x%x", devctl, int_usb);

	/* in host mode, the peripheral may issue remote wakeup.
	 * in peripheral mode, the host may resume the link.
	 * spurious RESUME irqs happen too, paired with SUSPEND.
	 */
	if (int_usb & MUSB_INTR_RESUME) {
		musb_handle_intr_resume(musb, devctl);
		handled = IRQ_HANDLED;
	}

	/* see manual for the order of the tests */
	if (int_usb & MUSB_INTR_SESSREQ) {
		if (musb_handle_intr_sessreq(musb, devctl))
			return IRQ_HANDLED;
		handled = IRQ_HANDLED;
	}

	if (int_usb & MUSB_INTR_VBUSERROR) {
		musb_handle_intr_vbuserr(musb, devctl);
		handled = IRQ_HANDLED;
	}

	if (int_usb & MUSB_INTR_SUSPEND) {
		musb_handle_intr_suspend(musb, devctl);
		handled = IRQ_HANDLED;
	}

	if (int_usb & MUSB_INTR_CONNECT) {
		musb_handle_intr_connect(musb, devctl, int_usb);
		handled = IRQ_HANDLED;
	}

	if (int_usb & MUSB_INTR_DISCONNECT) {
		musb_handle_intr_disconnect(musb, devctl);
		handled = IRQ_HANDLED;
	}

	if (int_usb & MUSB_INTR_RESET) {
		musb_handle_intr_reset(musb);
		handled = IRQ_HANDLED;
	}

#if 0
/* REVISIT ... this would be for multiplexing periodic endpoints, or
 * supporting transfer phasing to prevent exceeding ISO bandwidth
 * limits of a given frame or microframe.
 *
 * It's not needed for peripheral side, which dedicates endpoints;
 * though it _might_ use SOF irqs for other purposes.
 *
 * And it's not currently needed for host side, which also dedicates
 * endpoints, relies on TX/RX interval registers, and isn't claimed
 * to support ISO transfers yet.
 */
	if (int_usb & MUSB_INTR_SOF) {
		void __iomem *mbase = musb->mregs;
		struct musb_hw_ep	*ep;
		u8 epnum;
		u16 frame;

		dev_dbg(musb->controller, "START_OF_FRAME\n");
		handled = IRQ_HANDLED;

		/* start any periodic Tx transfers waiting for current frame */
		frame = musb_readw(mbase, MUSB_FRAME);
		ep = musb->endpoints;
		for (epnum = 1; (epnum < musb->nr_endpoints)
					&& (musb->epmask >= (1 << epnum));
				epnum++, ep++) {
			/*
			 * FIXME handle framecounter wraps (12 bits)
			 * eliminate duplicated StartUrb logic
			 */
			if (ep->dwWaitFrame >= frame) {
				ep->dwWaitFrame = 0;
				pr_debug("SOF --> periodic TX%s on %d\n",
					ep->tx_channel ? " DMA" : "",
					epnum);
				if (!ep->tx_channel)
					musb_h_tx_start(musb, epnum);
				else
					cppi_hostdma_start(musb, epnum);
			}
		}		/* end of for loop */
	}
#endif

	schedule_delayed_work(&musb->irq_work, 0);

	return handled;
}