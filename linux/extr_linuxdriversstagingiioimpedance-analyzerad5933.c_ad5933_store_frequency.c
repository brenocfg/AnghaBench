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
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad5933_state {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long AD5933_MAX_OUTPUT_FREQ_Hz ; 
 int EINVAL ; 
 int ad5933_set_freq (struct ad5933_state*,int /*<<< orphan*/ ,unsigned long) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad5933_state* iio_priv (struct iio_dev*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad5933_store_frequency(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf,
				      size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad5933_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	if (val > AD5933_MAX_OUTPUT_FREQ_Hz)
		return -EINVAL;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;
	ret = ad5933_set_freq(st, this_attr->address, val);
	iio_device_release_direct_mode(indio_dev);

	return ret ? ret : len;
}