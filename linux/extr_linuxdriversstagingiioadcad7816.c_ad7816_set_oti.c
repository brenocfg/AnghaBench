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
typedef  scalar_t__ u8 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7816_chip_info {size_t channel_id; scalar_t__* oti_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 long AD7816_BOUND_VALUE_BASE ; 
 long AD7816_BOUND_VALUE_MAX ; 
 long AD7816_BOUND_VALUE_MIN ; 
 size_t AD7816_CS_MAX ; 
 int EINVAL ; 
 int EIO ; 
 int ad7816_spi_write (struct ad7816_chip_info*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtol (char const*,int,long*) ; 

__attribute__((used)) static inline ssize_t ad7816_set_oti(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf,
				     size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);
	long value;
	u8 data;
	int ret;

	ret = kstrtol(buf, 10, &value);
	if (ret)
		return ret;

	if (chip->channel_id > AD7816_CS_MAX) {
		dev_err(dev, "Invalid oti channel id %d.\n", chip->channel_id);
		return -EINVAL;
	} else if (chip->channel_id == 0) {
		if (value < AD7816_BOUND_VALUE_MIN ||
		    value > AD7816_BOUND_VALUE_MAX)
			return -EINVAL;

		data = (u8)(value - AD7816_BOUND_VALUE_MIN +
			AD7816_BOUND_VALUE_BASE);
	} else {
		if (value < AD7816_BOUND_VALUE_BASE || value > 255)
			return -EINVAL;

		data = (u8)value;
	}

	ret = ad7816_spi_write(chip, data);
	if (ret)
		return -EIO;

	chip->oti_data[chip->channel_id] = data;

	return len;
}