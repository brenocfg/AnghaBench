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
struct xusb_udc {struct xusb_ep* ep; } ;
struct xusb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int XUSB_MAX_ENDPOINTS ; 
 int /*<<< orphan*/  xudc_nuke (struct xusb_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xudc_stop_activity(struct xusb_udc *udc)
{
	int i;
	struct xusb_ep *ep;

	for (i = 0; i < XUSB_MAX_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		xudc_nuke(ep, -ESHUTDOWN);
	}
}