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
typedef  int /*<<< orphan*/  u16 ;
struct usb_host_endpoint {struct dwc2_qh* hcpriv; } ;
struct dwc2_qh {int /*<<< orphan*/  host_us; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline u16 dwc2_hcd_get_ep_bandwidth(struct dwc2_hsotg *hsotg,
					    struct usb_host_endpoint *ep)
{
	struct dwc2_qh *qh = ep->hcpriv;

	if (!qh) {
		WARN_ON(1);
		return 0;
	}

	return qh->host_us;
}