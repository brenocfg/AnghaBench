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
struct usb_role_switch {int (* set ) (int /*<<< orphan*/ ,int) ;int role; int /*<<< orphan*/  lock; TYPE_1__ dev; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct usb_role_switch*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int usb_role_switch_set_role(struct usb_role_switch *sw, enum usb_role role)
{
	int ret;

	if (IS_ERR_OR_NULL(sw))
		return 0;

	mutex_lock(&sw->lock);

	ret = sw->set(sw->dev.parent, role);
	if (!ret)
		sw->role = role;

	mutex_unlock(&sw->lock);

	return ret;
}