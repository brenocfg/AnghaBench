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
struct omap2430_glue {scalar_t__ status; int /*<<< orphan*/  control_otghs; } ;
struct musb {struct device* controller; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ MUSB_UNKNOWN ; 
 int /*<<< orphan*/  USB_MODE_DISCONNECT ; 
 struct omap2430_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_control_usb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2430_musb_disable(struct musb *musb)
{
	struct device *dev = musb->controller;
	struct omap2430_glue *glue = dev_get_drvdata(dev->parent);

	if (glue->status != MUSB_UNKNOWN)
		omap_control_usb_set_mode(glue->control_otghs,
			USB_MODE_DISCONNECT);
}