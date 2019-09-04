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
struct iio_dev_attr {int address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7280_state {int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ad7280_write (struct ad7280_state*,int,int,int /*<<< orphan*/ ,unsigned long) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7280_state* iio_priv (struct iio_dev*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7280_store_balance_timer(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf,
					  size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7280_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	val /= 71500;

	if (val > 31)
		return -EINVAL;

	mutex_lock(&st->lock);
	ret = ad7280_write(st, this_attr->address >> 8,
			   this_attr->address & 0xFF,
			   0, (val & 0x1F) << 3);
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}