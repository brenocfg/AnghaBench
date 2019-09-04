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
struct iio_chan_spec {size_t channel; size_t differential; int /*<<< orphan*/  type; } ;
struct ad7746_chip_info {int** capdac; size_t capdac_set; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int AD7746_CAPDAC_DACEN ; 
 int AD7746_CAPDAC_DACP (int) ; 
 int /*<<< orphan*/  AD7746_REG_CAPDACA ; 
 int /*<<< orphan*/  AD7746_REG_CAPDACB ; 
 int AD7746_REG_CAP_GAINH ; 
 int AD7746_REG_CAP_OFFH ; 
 int AD7746_REG_VOLT_GAINH ; 
 int EINVAL ; 
#define  IIO_CAPACITANCE 133 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_CALIBSCALE 131 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_VOLTAGE 128 
 int ad7746_store_cap_filter_rate_setup (struct ad7746_chip_info*,int) ; 
 int ad7746_store_vt_filter_rate_setup (struct ad7746_chip_info*,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int,int) ; 
 struct ad7746_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7746_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct ad7746_chip_info *chip = iio_priv(indio_dev);
	int ret, reg;

	mutex_lock(&chip->lock);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val != 1) {
			ret = -EINVAL;
			goto out;
		}

		val = (val2 * 1024) / 15625;

		switch (chan->type) {
		case IIO_CAPACITANCE:
			reg = AD7746_REG_CAP_GAINH;
			break;
		case IIO_VOLTAGE:
			reg = AD7746_REG_VOLT_GAINH;
			break;
		default:
			ret = -EINVAL;
			goto out;
		}

		ret = i2c_smbus_write_word_swapped(chip->client, reg, val);
		if (ret < 0)
			goto out;

		ret = 0;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		if (val < 0 || val > 0xFFFF) {
			ret = -EINVAL;
			goto out;
		}
		ret = i2c_smbus_write_word_swapped(chip->client,
						   AD7746_REG_CAP_OFFH, val);
		if (ret < 0)
			goto out;

		ret = 0;
		break;
	case IIO_CHAN_INFO_OFFSET:
		if (val < 0 || val > 43008000) { /* 21pF */
			ret = -EINVAL;
			goto out;
		}

		/*
		 * CAPDAC Scale = 21pF_typ / 127
		 * CIN Scale = 8.192pF / 2^24
		 * Offset Scale = CAPDAC Scale / CIN Scale = 338646
		 */

		val /= 338646;

		chip->capdac[chan->channel][chan->differential] = val > 0 ?
			AD7746_CAPDAC_DACP(val) | AD7746_CAPDAC_DACEN : 0;

		ret = i2c_smbus_write_byte_data(chip->client,
						AD7746_REG_CAPDACA,
						chip->capdac[chan->channel][0]);
		if (ret < 0)
			goto out;
		ret = i2c_smbus_write_byte_data(chip->client,
						AD7746_REG_CAPDACB,
						chip->capdac[chan->channel][1]);
		if (ret < 0)
			goto out;

		chip->capdac_set = chan->channel;

		ret = 0;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val2) {
			ret = -EINVAL;
			goto out;
		}

		switch (chan->type) {
		case IIO_CAPACITANCE:
			ret = ad7746_store_cap_filter_rate_setup(chip, val);
			break;
		case IIO_VOLTAGE:
			ret = ad7746_store_vt_filter_rate_setup(chip, val);
			break;
		default:
			ret = -EINVAL;
		}
		break;
	default:
		ret = -EINVAL;
	}

out:
	mutex_unlock(&chip->lock);
	return ret;
}