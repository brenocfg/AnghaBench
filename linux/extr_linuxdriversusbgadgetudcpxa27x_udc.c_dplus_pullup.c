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
struct pxa_udc {int pullup_on; int /*<<< orphan*/  (* udc_command ) (int /*<<< orphan*/ ) ;scalar_t__ gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXA2XX_UDC_CMD_CONNECT ; 
 int /*<<< orphan*/  PXA2XX_UDC_CMD_DISCONNECT ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dplus_pullup(struct pxa_udc *udc, int on)
{
	if (udc->gpiod) {
		gpiod_set_value(udc->gpiod, on);
	} else if (udc->udc_command) {
		if (on)
			udc->udc_command(PXA2XX_UDC_CMD_CONNECT);
		else
			udc->udc_command(PXA2XX_UDC_CMD_DISCONNECT);
	}
	udc->pullup_on = on;
}