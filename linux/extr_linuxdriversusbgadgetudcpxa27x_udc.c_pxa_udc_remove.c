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
struct pxa_udc {int /*<<< orphan*/  clk; int /*<<< orphan*/ * transceiver; int /*<<< orphan*/  gadget; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct pxa_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa27x_udc_phy ; 
 int /*<<< orphan*/  pxa_cleanup_debugfs (struct pxa_udc*) ; 
 int /*<<< orphan*/ * the_controller ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_udc_remove(struct platform_device *_dev)
{
	struct pxa_udc *udc = platform_get_drvdata(_dev);

	usb_del_gadget_udc(&udc->gadget);
	pxa_cleanup_debugfs(udc);

	if (!IS_ERR_OR_NULL(udc->transceiver)) {
		usb_unregister_notifier(udc->transceiver, &pxa27x_udc_phy);
		usb_put_phy(udc->transceiver);
	}

	udc->transceiver = NULL;
	the_controller = NULL;
	clk_unprepare(udc->clk);

	return 0;
}