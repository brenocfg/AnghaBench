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
struct wrapper_priv_data {int /*<<< orphan*/ * dwc_otg_hcd; } ;
struct usb_hcd {scalar_t__ hcd_priv; } ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */

__attribute__((used)) static inline dwc_otg_hcd_t *hcd_to_dwc_otg_hcd(struct usb_hcd *hcd)
{
	struct wrapper_priv_data *p;
	p = (struct wrapper_priv_data *)(hcd->hcd_priv);
	return p->dwc_otg_hcd;
}