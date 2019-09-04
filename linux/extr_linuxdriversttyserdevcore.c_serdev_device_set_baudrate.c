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
struct TYPE_2__ {unsigned int (* set_baudrate ) (struct serdev_controller*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int stub1 (struct serdev_controller*,unsigned int) ; 

unsigned int serdev_device_set_baudrate(struct serdev_device *serdev, unsigned int speed)
{
	struct serdev_controller *ctrl = serdev->ctrl;

	if (!ctrl || !ctrl->ops->set_baudrate)
		return 0;

	return ctrl->ops->set_baudrate(ctrl, speed);

}