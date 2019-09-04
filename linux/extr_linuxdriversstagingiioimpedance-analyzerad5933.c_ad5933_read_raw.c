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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct ad5933_state {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AD5933_CTRL_MEASURE_TEMP ; 
 int /*<<< orphan*/  AD5933_REG_TEMP_DATA ; 
 int /*<<< orphan*/  AD5933_STAT_TEMP_VALID ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int ad5933_cmd (struct ad5933_state*,int /*<<< orphan*/ ) ; 
 int ad5933_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ad5933_wait_busy (struct ad5933_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad5933_state* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad5933_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad5933_state *st = iio_priv(indio_dev);
	__be16 dat;
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		ret = ad5933_cmd(st, AD5933_CTRL_MEASURE_TEMP);
		if (ret < 0)
			goto out;
		ret = ad5933_wait_busy(st, AD5933_STAT_TEMP_VALID);
		if (ret < 0)
			goto out;

		ret = ad5933_i2c_read(st->client,
				      AD5933_REG_TEMP_DATA,
				      2, (u8 *)&dat);
		if (ret < 0)
			goto out;
		iio_device_release_direct_mode(indio_dev);
		*val = sign_extend32(be16_to_cpu(dat), 13);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 1000;
		*val2 = 5;
		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
out:
	iio_device_release_direct_mode(indio_dev);
	return ret;
}