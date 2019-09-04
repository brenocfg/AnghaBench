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
struct musb {int dyn_fifo; int /*<<< orphan*/  isr; int /*<<< orphan*/  xceiv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  jz4740_musb_interrupt ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usb_get_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_phy_generic_register () ; 

__attribute__((used)) static int jz4740_musb_init(struct musb *musb)
{
	usb_phy_generic_register();
	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	if (IS_ERR(musb->xceiv)) {
		pr_err("HS UDC: no transceiver configured\n");
		return PTR_ERR(musb->xceiv);
	}

	/* Silicon does not implement ConfigData register.
	 * Set dyn_fifo to avoid reading EP config from hardware.
	 */
	musb->dyn_fifo = true;

	musb->isr = jz4740_musb_interrupt;

	return 0;
}