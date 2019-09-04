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
struct serdev_device {struct serdev_controller* ctrl; } ;
struct serdev_controller {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_tiocm ) (struct serdev_controller*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct serdev_controller*) ; 

int serdev_device_get_tiocm(struct serdev_device *serdev)
{
	struct serdev_controller *ctrl = serdev->ctrl;

	if (!ctrl || !ctrl->ops->get_tiocm)
		return -ENOTSUPP;

	return ctrl->ops->get_tiocm(ctrl);
}