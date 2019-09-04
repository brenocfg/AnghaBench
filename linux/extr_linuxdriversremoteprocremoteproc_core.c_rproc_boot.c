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
struct device {int dummy; } ;
struct rproc {int name; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  power; int /*<<< orphan*/  firmware; struct device dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ RPROC_DELETED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 int rproc_fw_boot (struct rproc*,struct firmware const*) ; 

int rproc_boot(struct rproc *rproc)
{
	const struct firmware *firmware_p;
	struct device *dev;
	int ret;

	if (!rproc) {
		pr_err("invalid rproc handle\n");
		return -EINVAL;
	}

	dev = &rproc->dev;

	ret = mutex_lock_interruptible(&rproc->lock);
	if (ret) {
		dev_err(dev, "can't lock rproc %s: %d\n", rproc->name, ret);
		return ret;
	}

	if (rproc->state == RPROC_DELETED) {
		ret = -ENODEV;
		dev_err(dev, "can't boot deleted rproc %s\n", rproc->name);
		goto unlock_mutex;
	}

	/* skip the boot process if rproc is already powered up */
	if (atomic_inc_return(&rproc->power) > 1) {
		ret = 0;
		goto unlock_mutex;
	}

	dev_info(dev, "powering up %s\n", rproc->name);

	/* load firmware */
	ret = request_firmware(&firmware_p, rproc->firmware, dev);
	if (ret < 0) {
		dev_err(dev, "request_firmware failed: %d\n", ret);
		goto downref_rproc;
	}

	ret = rproc_fw_boot(rproc, firmware_p);

	release_firmware(firmware_p);

downref_rproc:
	if (ret)
		atomic_dec(&rproc->power);
unlock_mutex:
	mutex_unlock(&rproc->lock);
	return ret;
}