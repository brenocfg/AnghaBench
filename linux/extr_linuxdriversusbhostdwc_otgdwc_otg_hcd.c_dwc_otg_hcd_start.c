#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_hcd_function_ops {int dummy; } ;
struct TYPE_7__ {TYPE_3__* core_if; struct dwc_otg_hcd_function_ops* fops; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
struct TYPE_6__ {scalar_t__ adp_started; } ;
struct TYPE_8__ {TYPE_1__ adp; int /*<<< orphan*/  adp_enable; } ;

/* Variables and functions */
 int DWC_E_NO_DEVICE ; 
 int /*<<< orphan*/  dwc_otg_hcd_reinit (TYPE_2__*) ; 
 int /*<<< orphan*/  dwc_otg_is_device_mode (TYPE_3__*) ; 

int dwc_otg_hcd_start(dwc_otg_hcd_t * hcd,
		      struct dwc_otg_hcd_function_ops *fops)
{
	int retval = 0;

	hcd->fops = fops;
	if (!dwc_otg_is_device_mode(hcd->core_if) &&
		(!hcd->core_if->adp_enable || hcd->core_if->adp.adp_started)) {
		dwc_otg_hcd_reinit(hcd);
	} else {
		retval = -DWC_E_NO_DEVICE;
	}

	return retval;
}