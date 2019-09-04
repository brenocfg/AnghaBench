#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data_toggle; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int DWC_E_INVALID ; 
 int /*<<< orphan*/  DWC_OTG_HC_PID_DATA0 ; 

int dwc_otg_hcd_endpoint_reset(dwc_otg_hcd_t * hcd, void *ep_handle)
{
	int retval = 0;
	dwc_otg_qh_t *qh = (dwc_otg_qh_t *) ep_handle;
	if (!qh)
		return -DWC_E_INVALID;

	qh->data_toggle = DWC_OTG_HC_PID_DATA0;
	return retval;
}