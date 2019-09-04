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
struct sst_device {int /*<<< orphan*/  name; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sst_device* sst ; 
 int /*<<< orphan*/  sst_lock ; 

int sst_unregister_dsp(struct sst_device *dev)
{
	if (WARN_ON(!dev))
		return -EINVAL;
	if (dev != sst)
		return -EINVAL;

	mutex_lock(&sst_lock);

	if (!sst) {
		mutex_unlock(&sst_lock);
		return -EIO;
	}

	module_put(sst->dev->driver->owner);
	dev_dbg(dev->dev, "unreg %s\n", sst->name);
	sst = NULL;
	mutex_unlock(&sst_lock);
	return 0;
}