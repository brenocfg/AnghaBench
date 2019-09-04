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
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ can_support_ecm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_ecm ; 
 int /*<<< orphan*/  f_eem ; 
 int /*<<< orphan*/  f_geth ; 
 int /*<<< orphan*/  f_rndis ; 
 int /*<<< orphan*/  fi_ecm ; 
 int /*<<< orphan*/  fi_eem ; 
 int /*<<< orphan*/  fi_geth ; 
 int /*<<< orphan*/  fi_rndis ; 
 scalar_t__ has_rndis () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** otg_desc ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 
 scalar_t__ use_eem ; 

__attribute__((used)) static int eth_unbind(struct usb_composite_dev *cdev)
{
	if (has_rndis()) {
		usb_put_function(f_rndis);
		usb_put_function_instance(fi_rndis);
	}
	if (use_eem) {
		usb_put_function(f_eem);
		usb_put_function_instance(fi_eem);
	} else if (can_support_ecm(cdev->gadget)) {
		usb_put_function(f_ecm);
		usb_put_function_instance(fi_ecm);
	} else {
		usb_put_function(f_geth);
		usb_put_function_instance(fi_geth);
	}
	kfree(otg_desc[0]);
	otg_desc[0] = NULL;

	return 0;
}