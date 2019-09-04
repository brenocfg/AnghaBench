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
struct usb_hcd {int dummy; } ;
struct imx21 {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ USBH_FRMNUB ; 
 struct imx21* hcd_to_imx21 (struct usb_hcd*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int wrap_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx21_hc_get_frame(struct usb_hcd *hcd)
{
	struct imx21 *imx21 = hcd_to_imx21(hcd);

	return wrap_frame(readl(imx21->regs + USBH_FRMNUB));
}