#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct serdev_controller {int nr; TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ctrl_ida ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,struct serdev_controller*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct serdev_controller*) ; 
 struct serdev_controller* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (TYPE_1__*,int) ; 
 int /*<<< orphan*/  serdev_bus_type ; 
 int /*<<< orphan*/  serdev_controller_set_drvdata (struct serdev_controller*,struct serdev_controller*) ; 
 int /*<<< orphan*/  serdev_ctrl_type ; 

struct serdev_controller *serdev_controller_alloc(struct device *parent,
					      size_t size)
{
	struct serdev_controller *ctrl;
	int id;

	if (WARN_ON(!parent))
		return NULL;

	ctrl = kzalloc(sizeof(*ctrl) + size, GFP_KERNEL);
	if (!ctrl)
		return NULL;

	id = ida_simple_get(&ctrl_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		dev_err(parent,
			"unable to allocate serdev controller identifier.\n");
		goto err_free;
	}

	ctrl->nr = id;

	device_initialize(&ctrl->dev);
	ctrl->dev.type = &serdev_ctrl_type;
	ctrl->dev.bus = &serdev_bus_type;
	ctrl->dev.parent = parent;
	ctrl->dev.of_node = parent->of_node;
	serdev_controller_set_drvdata(ctrl, &ctrl[1]);

	dev_set_name(&ctrl->dev, "serial%d", id);

	pm_runtime_no_callbacks(&ctrl->dev);
	pm_suspend_ignore_children(&ctrl->dev, true);

	dev_dbg(&ctrl->dev, "allocated controller 0x%p id %d\n", ctrl, id);
	return ctrl;

err_free:
	kfree(ctrl);

	return NULL;
}