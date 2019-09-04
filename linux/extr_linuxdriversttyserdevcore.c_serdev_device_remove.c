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
struct serdev_device {int /*<<< orphan*/  dev; struct serdev_controller* ctrl; } ;
struct serdev_controller {int /*<<< orphan*/ * serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

void serdev_device_remove(struct serdev_device *serdev)
{
	struct serdev_controller *ctrl = serdev->ctrl;

	device_unregister(&serdev->dev);
	ctrl->serdev = NULL;
}