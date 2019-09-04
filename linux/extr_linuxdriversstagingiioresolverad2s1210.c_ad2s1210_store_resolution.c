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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad2s1210_state {unsigned char resolution; int /*<<< orphan*/  lock; TYPE_1__* pdata; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ gpioin; } ;

/* Variables and functions */
 unsigned char AD2S1210_MSB_IS_HIGH ; 
 unsigned char AD2S1210_MSB_IS_LOW ; 
 unsigned char AD2S1210_REG_CONTROL ; 
 unsigned char AD2S1210_SET_RESOLUTION ; 
 int EINVAL ; 
 int EIO ; 
 int ad2s1210_config_read (struct ad2s1210_state*,unsigned char) ; 
 int ad2s1210_config_write (struct ad2s1210_state*,unsigned char) ; 
 unsigned char ad2s1210_read_resolution_pin (struct ad2s1210_state*) ; 
 unsigned char* ad2s1210_resolution_value ; 
 int /*<<< orphan*/  ad2s1210_set_resolution_pin (struct ad2s1210_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct ad2s1210_state* iio_priv (int /*<<< orphan*/ ) ; 
 int kstrtou8 (char const*,int,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ad2s1210_store_resolution(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	unsigned char data;
	unsigned char udata;
	int ret;

	ret = kstrtou8(buf, 10, &udata);
	if (ret || udata < 10 || udata > 16) {
		dev_err(dev, "ad2s1210: resolution out of range\n");
		return -EINVAL;
	}
	mutex_lock(&st->lock);
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = ret;
	data &= ~AD2S1210_SET_RESOLUTION;
	data |= (udata - 10) >> 1;
	ret = ad2s1210_config_write(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_write(st, data & AD2S1210_MSB_IS_LOW);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = ret;
	if (data & AD2S1210_MSB_IS_HIGH) {
		ret = -EIO;
		dev_err(dev, "ad2s1210: setting resolution fail\n");
		goto error_ret;
	}
	st->resolution
		= ad2s1210_resolution_value[data & AD2S1210_SET_RESOLUTION];
	if (st->pdata->gpioin) {
		data = ad2s1210_read_resolution_pin(st);
		if (data != st->resolution)
			dev_warn(dev, "ad2s1210: resolution settings not match\n");
	} else {
		ad2s1210_set_resolution_pin(st);
	}
	ret = len;
error_ret:
	mutex_unlock(&st->lock);
	return ret;
}