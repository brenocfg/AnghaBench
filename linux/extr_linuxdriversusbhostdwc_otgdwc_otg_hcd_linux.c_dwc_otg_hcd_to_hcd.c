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
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 struct usb_hcd* dwc_otg_hcd_get_priv_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct usb_hcd *dwc_otg_hcd_to_hcd(dwc_otg_hcd_t * dwc_otg_hcd)
{
	return dwc_otg_hcd_get_priv_data(dwc_otg_hcd);
}