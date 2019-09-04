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
struct usb_host_endpoint {struct dwc2_qh* hcpriv; } ;
struct dwc2_qh {int /*<<< orphan*/  data_toggle; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_HC_PID_DATA0 ; 
 int EINVAL ; 

__attribute__((used)) static int dwc2_hcd_endpoint_reset(struct dwc2_hsotg *hsotg,
				   struct usb_host_endpoint *ep)
{
	struct dwc2_qh *qh = ep->hcpriv;

	if (!qh)
		return -EINVAL;

	qh->data_toggle = DWC2_HC_PID_DATA0;

	return 0;
}