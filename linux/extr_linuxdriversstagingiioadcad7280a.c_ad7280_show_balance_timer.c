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
 int ad7280_read (struct ad7280_state*,int,int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7280_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,unsigned int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7280_show_balance_timer(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7280_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret;
	unsigned int msecs;

	mutex_lock(&st->lock);
	ret = ad7280_read(st, this_attr->address >> 8,
			  this_attr->address & 0xFF);
	mutex_unlock(&st->lock);

	if (ret < 0)
		return ret;

	msecs = (ret >> 3) * 71500;

	return sprintf(buf, "%u\n", msecs);
}