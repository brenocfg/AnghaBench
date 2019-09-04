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
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
struct ad7152_chip_info {int filter_rate_setup; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7152_CFG2_OSR (int) ; 
 int /*<<< orphan*/  AD7152_REG_CFG2 ; 
 int ARRAY_SIZE (int**) ; 
 int** ad7152_filter_rate_table ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7152_chip_info* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7152_write_raw_samp_freq(struct device *dev, int val)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7152_chip_info *chip = iio_priv(indio_dev);
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(ad7152_filter_rate_table); i++)
		if (val >= ad7152_filter_rate_table[i][0])
			break;

	if (i >= ARRAY_SIZE(ad7152_filter_rate_table))
		i = ARRAY_SIZE(ad7152_filter_rate_table) - 1;

	ret = i2c_smbus_write_byte_data(chip->client,
					AD7152_REG_CFG2, AD7152_CFG2_OSR(i));
	if (ret < 0)
		return ret;

	chip->filter_rate_setup = i;

	return ret;
}