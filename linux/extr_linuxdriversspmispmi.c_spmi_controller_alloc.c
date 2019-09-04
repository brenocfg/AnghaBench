#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct spmi_controller {int nr; TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ctrl_ida ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,struct spmi_controller*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spmi_controller* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spmi_bus_type ; 
 int /*<<< orphan*/  spmi_controller_put (struct spmi_controller*) ; 
 int /*<<< orphan*/  spmi_controller_set_drvdata (struct spmi_controller*,struct spmi_controller*) ; 
 int /*<<< orphan*/  spmi_ctrl_type ; 

struct spmi_controller *spmi_controller_alloc(struct device *parent,
					      size_t size)
{
	struct spmi_controller *ctrl;
	int id;

	if (WARN_ON(!parent))
		return NULL;

	ctrl = kzalloc(sizeof(*ctrl) + size, GFP_KERNEL);
	if (!ctrl)
		return NULL;

	device_initialize(&ctrl->dev);
	ctrl->dev.type = &spmi_ctrl_type;
	ctrl->dev.bus = &spmi_bus_type;
	ctrl->dev.parent = parent;
	ctrl->dev.of_node = parent->of_node;
	spmi_controller_set_drvdata(ctrl, &ctrl[1]);

	id = ida_simple_get(&ctrl_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		dev_err(parent,
			"unable to allocate SPMI controller identifier.\n");
		spmi_controller_put(ctrl);
		return NULL;
	}

	ctrl->nr = id;
	dev_set_name(&ctrl->dev, "spmi-%d", id);

	dev_dbg(&ctrl->dev, "allocated controller 0x%p id %d\n", ctrl, id);
	return ctrl;
}