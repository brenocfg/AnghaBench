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
struct usbhs_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UGCTRL2_USB0SEL_EHCI ; 
 int /*<<< orphan*/  UGCTRL2_USB0SEL_HSUSB ; 
 int /*<<< orphan*/  usbhs_rcar3_set_ugctrl2 (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhs_rcar3_set_usbsel(struct usbhs_priv *priv, bool ehci)
{
	if (ehci)
		usbhs_rcar3_set_ugctrl2(priv, UGCTRL2_USB0SEL_EHCI);
	else
		usbhs_rcar3_set_ugctrl2(priv, UGCTRL2_USB0SEL_HSUSB);
}