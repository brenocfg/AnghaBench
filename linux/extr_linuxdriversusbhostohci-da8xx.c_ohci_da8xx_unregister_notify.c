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
struct TYPE_2__ {struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct device {int dummy; } ;
struct da8xx_ohci_root_hub {int /*<<< orphan*/  (* ocic_notify ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct da8xx_ohci_root_hub* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ohci_da8xx_unregister_notify(struct usb_hcd *hcd)
{
	struct device *dev		= hcd->self.controller;
	struct da8xx_ohci_root_hub *hub	= dev_get_platdata(dev);

	if (hub && hub->ocic_notify)
		hub->ocic_notify(NULL);
}