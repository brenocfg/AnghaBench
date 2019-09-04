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
typedef  int u8 ;
struct w1_slave {struct w1_master* master; } ;
struct w1_master {int /*<<< orphan*/  bus_mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct w1_slave* dev_to_w1_slave (struct device*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_ds2405_select (struct w1_slave*,int) ; 
 int w1_read_8 (struct w1_master*) ; 
 int /*<<< orphan*/  w1_reset_bus (struct w1_master*) ; 

__attribute__((used)) static ssize_t state_show(struct device *device,
			  struct device_attribute *attr, char *buf)
{
	struct w1_slave *sl = dev_to_w1_slave(device);
	struct w1_master *dev = sl->master;

	int ret;
	ssize_t f_retval;
	u8 state;

	ret = mutex_lock_interruptible(&dev->bus_mutex);
	if (ret)
		return ret;

	if (!w1_ds2405_select(sl, false)) {
		f_retval = -ENODEV;
		goto out_unlock;
	}

	state = w1_read_8(dev);
	if (state != 0 &&
	    state != 0xff) {
		dev_err(device, "non-consistent state %x\n", state);
		f_retval = -EIO;
		goto out_unlock;
	}

	*buf = state ? '1' : '0';
	f_retval = 1;

out_unlock:
	w1_reset_bus(dev);
	mutex_unlock(&dev->bus_mutex);

	return f_retval;
}