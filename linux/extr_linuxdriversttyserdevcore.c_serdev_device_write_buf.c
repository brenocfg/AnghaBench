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
struct TYPE_2__ {int (* write_buf ) (struct serdev_controller*,unsigned char const*,size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct serdev_controller*,unsigned char const*,size_t) ; 

int serdev_device_write_buf(struct serdev_device *serdev,
			    const unsigned char *buf, size_t count)
{
	struct serdev_controller *ctrl = serdev->ctrl;

	if (!ctrl || !ctrl->ops->write_buf)
		return -EINVAL;

	return ctrl->ops->write_buf(ctrl, buf, count);
}