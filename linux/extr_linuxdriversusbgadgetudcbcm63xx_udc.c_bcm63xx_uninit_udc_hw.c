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
struct bcm63xx_udc {int /*<<< orphan*/  usbh_clk; int /*<<< orphan*/  usbd_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iudma_uninit (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  set_clocks (struct bcm63xx_udc*,int) ; 

__attribute__((used)) static void bcm63xx_uninit_udc_hw(struct bcm63xx_udc *udc)
{
	set_clocks(udc, true);
	iudma_uninit(udc);
	set_clocks(udc, false);

	clk_put(udc->usbd_clk);
	clk_put(udc->usbh_clk);
}