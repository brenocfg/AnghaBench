#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct typec_switch {TYPE_2__* dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct typec_switch*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct typec_switch* device_connection_find_match (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_lock ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_switch_match ; 

struct typec_switch *typec_switch_get(struct device *dev)
{
	struct typec_switch *sw;

	mutex_lock(&switch_lock);
	sw = device_connection_find_match(dev, "typec-switch", NULL,
					  typec_switch_match);
	if (!IS_ERR_OR_NULL(sw)) {
		WARN_ON(!try_module_get(sw->dev->driver->owner));
		get_device(sw->dev);
	}
	mutex_unlock(&switch_lock);

	return sw;
}