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
struct usb_function {int dummy; } ;
struct usb_configuration {int dummy; } ;
struct f_hidg {int /*<<< orphan*/  cdev; int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f_hidg* func_to_hidg (struct usb_function*) ; 
 int /*<<< orphan*/  hidg_class ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void hidg_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_hidg *hidg = func_to_hidg(f);

	device_destroy(hidg_class, MKDEV(major, hidg->minor));
	cdev_del(&hidg->cdev);

	usb_free_all_descriptors(f);
}