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
struct usb_composite_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * f_serial ; 
 int /*<<< orphan*/ * fi_serial ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int n_ports ; 
 int /*<<< orphan*/ ** otg_desc ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_unbind(struct usb_composite_dev *cdev)
{
	int i;

	for (i = 0; i < n_ports; i++) {
		usb_put_function(f_serial[i]);
		usb_put_function_instance(fi_serial[i]);
	}

	kfree(otg_desc[0]);
	otg_desc[0] = NULL;

	return 0;
}