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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {size_t channel; } ;
struct ad7152_chip_info {int /*<<< orphan*/  state_lock; int /*<<< orphan*/ * setup; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 size_t AD7152_GAIN ; 
 size_t AD7152_OFFS ; 
 size_t AD7152_SETUP ; 
 int /*<<< orphan*/  AD7152_SETUP_RANGE (int) ; 
 int /*<<< orphan*/  AD7152_SETUP_RANGE_4pF ; 
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 131 
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/ ** ad7152_addresses ; 
 int* ad7152_scale_table ; 
 int ad7152_write_raw_samp_freq (int /*<<< orphan*/ *,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7152_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swab16 (int) ; 

__attribute__((used)) static int ad7152_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct ad7152_chip_info *chip = iio_priv(indio_dev);
	int ret, i;

	mutex_lock(&chip->state_lock);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val != 1) {
			ret = -EINVAL;
			goto out;
		}

		val = (val2 * 1024) / 15625;

		ret = i2c_smbus_write_word_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_GAIN],
				swab16(val));
		if (ret < 0)
			goto out;

		ret = 0;
		break;

	case IIO_CHAN_INFO_CALIBBIAS:
		if ((val < 0) | (val > 0xFFFF)) {
			ret = -EINVAL;
			goto out;
		}
		ret = i2c_smbus_write_word_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_OFFS],
				swab16(val));
		if (ret < 0)
			goto out;

		ret = 0;
		break;
	case IIO_CHAN_INFO_SCALE:
		if (val) {
			ret = -EINVAL;
			goto out;
		}
		for (i = 0; i < ARRAY_SIZE(ad7152_scale_table); i++)
			if (val2 == ad7152_scale_table[i])
				break;

		chip->setup[chan->channel] &= ~AD7152_SETUP_RANGE_4pF;
		chip->setup[chan->channel] |= AD7152_SETUP_RANGE(i);

		ret = i2c_smbus_write_byte_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_SETUP],
				chip->setup[chan->channel]);
		if (ret < 0)
			goto out;

		ret = 0;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val2) {
			ret = -EINVAL;
			goto out;
		}
		ret = ad7152_write_raw_samp_freq(&indio_dev->dev, val);
		if (ret < 0)
			goto out;

		ret = 0;
		break;
	default:
		ret = -EINVAL;
	}

out:
	mutex_unlock(&chip->state_lock);
	return ret;
}