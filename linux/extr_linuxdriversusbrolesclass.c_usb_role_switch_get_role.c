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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct usb_role_switch {int (* get ) (int /*<<< orphan*/ ) ;int role; int /*<<< orphan*/  lock; TYPE_1__ dev; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct usb_role_switch*) ; 
 int USB_ROLE_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

enum usb_role usb_role_switch_get_role(struct usb_role_switch *sw)
{
	enum usb_role role;

	if (IS_ERR_OR_NULL(sw))
		return USB_ROLE_NONE;

	mutex_lock(&sw->lock);

	if (sw->get)
		role = sw->get(sw->dev.parent);
	else
		role = sw->role;

	mutex_unlock(&sw->lock);

	return role;
}