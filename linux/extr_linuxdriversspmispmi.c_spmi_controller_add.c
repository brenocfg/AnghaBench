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
struct spmi_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EAGAIN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_registered ; 
 int /*<<< orphan*/  of_spmi_register_devices (struct spmi_controller*) ; 

int spmi_controller_add(struct spmi_controller *ctrl)
{
	int ret;

	/* Can't register until after driver model init */
	if (WARN_ON(!is_registered))
		return -EAGAIN;

	ret = device_add(&ctrl->dev);
	if (ret)
		return ret;

	if (IS_ENABLED(CONFIG_OF))
		of_spmi_register_devices(ctrl);

	dev_dbg(&ctrl->dev, "spmi-%d registered: dev:%p\n",
		ctrl->nr, &ctrl->dev);

	return 0;
}