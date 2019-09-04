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
struct TYPE_2__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct serdev_device {int /*<<< orphan*/  write_lock; int /*<<< orphan*/  write_comp; TYPE_1__ dev; struct serdev_controller* ctrl; } ;
struct serdev_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct serdev_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_bus_type ; 
 int /*<<< orphan*/  serdev_device_type ; 

struct serdev_device *serdev_device_alloc(struct serdev_controller *ctrl)
{
	struct serdev_device *serdev;

	serdev = kzalloc(sizeof(*serdev), GFP_KERNEL);
	if (!serdev)
		return NULL;

	serdev->ctrl = ctrl;
	device_initialize(&serdev->dev);
	serdev->dev.parent = &ctrl->dev;
	serdev->dev.bus = &serdev_bus_type;
	serdev->dev.type = &serdev_device_type;
	init_completion(&serdev->write_comp);
	mutex_init(&serdev->write_lock);
	return serdev;
}