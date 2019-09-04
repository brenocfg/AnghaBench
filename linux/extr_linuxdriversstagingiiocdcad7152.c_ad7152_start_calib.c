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
struct iio_dev_attr {scalar_t__ address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7152_chip_info {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AD7152_CONF_CH1EN ; 
 int AD7152_CONF_CH2EN ; 
 int /*<<< orphan*/  AD7152_REG_CFG ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7152_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static inline ssize_t ad7152_start_calib(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t len,
					 u8 regval)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7152_chip_info *chip = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	bool doit;
	int ret, timeout = 10;

	ret = strtobool(buf, &doit);
	if (ret < 0)
		return ret;

	if (!doit)
		return 0;

	if (this_attr->address == 0)
		regval |= AD7152_CONF_CH1EN;
	else
		regval |= AD7152_CONF_CH2EN;

	mutex_lock(&chip->state_lock);
	ret = i2c_smbus_write_byte_data(chip->client, AD7152_REG_CFG, regval);
	if (ret < 0)
		goto unlock;

	do {
		mdelay(20);
		ret = i2c_smbus_read_byte_data(chip->client, AD7152_REG_CFG);
		if (ret < 0)
			goto unlock;

	} while ((ret == regval) && timeout--);

	mutex_unlock(&chip->state_lock);
	return len;

unlock:
	mutex_unlock(&chip->state_lock);
	return ret;
}