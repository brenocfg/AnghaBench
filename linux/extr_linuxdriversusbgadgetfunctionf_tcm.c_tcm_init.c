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

/* Variables and functions */
 int target_register_template (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcmusb_func ; 
 int usb_function_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_function_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbg_ops ; 

__attribute__((used)) static int tcm_init(void)
{
	int ret;

	ret = usb_function_register(&tcmusb_func);
	if (ret)
		return ret;

	ret = target_register_template(&usbg_ops);
	if (ret)
		usb_function_unregister(&tcmusb_func);

	return ret;
}