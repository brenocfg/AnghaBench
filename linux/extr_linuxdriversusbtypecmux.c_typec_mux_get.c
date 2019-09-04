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
struct typec_mux {TYPE_2__* dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct typec_mux*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct typec_mux* device_connection_find_match (struct device*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mux_lock ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_mux_match ; 

struct typec_mux *typec_mux_get(struct device *dev, const char *name)
{
	struct typec_mux *mux;

	mutex_lock(&mux_lock);
	mux = device_connection_find_match(dev, name, NULL, typec_mux_match);
	if (!IS_ERR_OR_NULL(mux)) {
		WARN_ON(!try_module_get(mux->dev->driver->owner));
		get_device(mux->dev);
	}
	mutex_unlock(&mux_lock);

	return mux;
}