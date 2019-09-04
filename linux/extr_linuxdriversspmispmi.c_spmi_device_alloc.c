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
struct spmi_device {TYPE_1__ dev; struct spmi_controller* ctrl; } ;
struct spmi_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct spmi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spmi_bus_type ; 
 int /*<<< orphan*/  spmi_dev_type ; 

struct spmi_device *spmi_device_alloc(struct spmi_controller *ctrl)
{
	struct spmi_device *sdev;

	sdev = kzalloc(sizeof(*sdev), GFP_KERNEL);
	if (!sdev)
		return NULL;

	sdev->ctrl = ctrl;
	device_initialize(&sdev->dev);
	sdev->dev.parent = &ctrl->dev;
	sdev->dev.bus = &spmi_bus_type;
	sdev->dev.type = &spmi_dev_type;
	return sdev;
}