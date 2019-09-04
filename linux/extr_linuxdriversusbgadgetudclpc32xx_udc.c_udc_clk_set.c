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
struct lpc32xx_udc {int clocked; int /*<<< orphan*/  usb_slv_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_clk_set(struct lpc32xx_udc *udc, int enable)
{
	if (enable != 0) {
		if (udc->clocked)
			return;

		udc->clocked = 1;
		clk_prepare_enable(udc->usb_slv_clk);
	} else {
		if (!udc->clocked)
			return;

		udc->clocked = 0;
		clk_disable_unprepare(udc->usb_slv_clk);
	}
}