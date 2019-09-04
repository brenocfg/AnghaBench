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
struct usb_configuration {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void eem_unbind(struct usb_configuration *c, struct usb_function *f)
{
	DBG(c->cdev, "eem unbind\n");

	usb_free_all_descriptors(f);
}