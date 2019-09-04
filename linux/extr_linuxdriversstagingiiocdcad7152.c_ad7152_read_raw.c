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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {size_t channel; int /*<<< orphan*/  differential; } ;
struct ad7152_chip_info {size_t filter_rate_setup; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  client; int /*<<< orphan*/ * setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7152_CONF_CH1EN ; 
 int /*<<< orphan*/  AD7152_CONF_CH2EN ; 
 int /*<<< orphan*/  AD7152_CONF_MODE_SINGLE_CONV ; 
 size_t AD7152_DATA ; 
 size_t AD7152_GAIN ; 
 size_t AD7152_OFFS ; 
 int /*<<< orphan*/  AD7152_REG_CFG ; 
 size_t AD7152_SETUP ; 
 int /*<<< orphan*/  AD7152_SETUP_CAPDIFF ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_CALIBSCALE 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/ ** ad7152_addresses ; 
 int /*<<< orphan*/ ** ad7152_filter_rate_table ; 
 int ad7152_read_raw_samp_freq (int /*<<< orphan*/ *,int*) ; 
 int* ad7152_scale_table ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7152_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int swab16 (int) ; 

__attribute__((used)) static int ad7152_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2,
			   long mask)
{
	struct ad7152_chip_info *chip = iio_priv(indio_dev);
	int ret;
	u8 regval = 0;

	mutex_lock(&chip->state_lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		/* First set whether in differential mode */

		regval = chip->setup[chan->channel];

		if (chan->differential)
			chip->setup[chan->channel] |= AD7152_SETUP_CAPDIFF;
		else
			chip->setup[chan->channel] &= ~AD7152_SETUP_CAPDIFF;

		if (regval != chip->setup[chan->channel]) {
			ret = i2c_smbus_write_byte_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_SETUP],
				chip->setup[chan->channel]);
			if (ret < 0)
				goto out;
		}
		/* Make sure the channel is enabled */
		if (chan->channel == 0)
			regval = AD7152_CONF_CH1EN;
		else
			regval = AD7152_CONF_CH2EN;

		/* Trigger a single read */
		regval |= AD7152_CONF_MODE_SINGLE_CONV;
		ret = i2c_smbus_write_byte_data(chip->client, AD7152_REG_CFG,
				regval);
		if (ret < 0)
			goto out;

		msleep(ad7152_filter_rate_table[chip->filter_rate_setup][1]);
		/* Now read the actual register */
		ret = i2c_smbus_read_word_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_DATA]);
		if (ret < 0)
			goto out;
		*val = swab16(ret);

		if (chan->differential)
			*val -= 0x8000;

		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_CALIBSCALE:

		ret = i2c_smbus_read_word_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_GAIN]);
		if (ret < 0)
			goto out;
		/* 1 + gain_val / 2^16 */
		*val = 1;
		*val2 = (15625 * swab16(ret)) / 1024;

		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_read_word_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_OFFS]);
		if (ret < 0)
			goto out;
		*val = swab16(ret);

		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_read_byte_data(chip->client,
				ad7152_addresses[chan->channel][AD7152_SETUP]);
		if (ret < 0)
			goto out;
		*val = 0;
		*val2 = ad7152_scale_table[ret >> 6];

		ret = IIO_VAL_INT_PLUS_NANO;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = ad7152_read_raw_samp_freq(&indio_dev->dev, val);
		if (ret < 0)
			goto out;

		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
	}
out:
	mutex_unlock(&chip->state_lock);
	return ret;
}