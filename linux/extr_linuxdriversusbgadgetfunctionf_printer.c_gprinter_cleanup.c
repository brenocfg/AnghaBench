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
 int /*<<< orphan*/  MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ major ; 
 scalar_t__ minors ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * usb_gadget_class ; 

__attribute__((used)) static void gprinter_cleanup(void)
{
	if (major) {
		unregister_chrdev_region(MKDEV(major, 0), minors);
		major = minors = 0;
	}
	class_destroy(usb_gadget_class);
	usb_gadget_class = NULL;
}