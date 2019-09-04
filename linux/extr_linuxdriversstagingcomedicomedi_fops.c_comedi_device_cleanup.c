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
struct module {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  mutex; scalar_t__ use_count; TYPE_1__* driver; scalar_t__ attached; } ;
struct TYPE_2__ {struct module* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_device_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void comedi_device_cleanup(struct comedi_device *dev)
{
	struct module *driver_module = NULL;

	if (!dev)
		return;
	mutex_lock(&dev->mutex);
	if (dev->attached)
		driver_module = dev->driver->module;
	comedi_device_detach(dev);
	if (driver_module && dev->use_count)
		module_put(driver_module);
	mutex_unlock(&dev->mutex);
}