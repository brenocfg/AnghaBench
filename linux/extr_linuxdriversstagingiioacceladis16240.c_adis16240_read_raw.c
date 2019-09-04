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
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  channel; int /*<<< orphan*/  type; } ;
struct adis {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16240_ERROR_ACTIVE ; 
 int EINVAL ; 
#define  IIO_ACCEL 136 
#define  IIO_CHAN_INFO_CALIBBIAS 135 
#define  IIO_CHAN_INFO_OFFSET 134 
#define  IIO_CHAN_INFO_PEAK 133 
#define  IIO_CHAN_INFO_PEAK_SCALE 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
 int IIO_G_TO_M_S_2 (int) ; 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VOLTAGE 128 
 int /*<<< orphan*/ ** adis16240_addresses ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int adis_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ,int*) ; 
 struct adis* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adis16240_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct adis *st = iio_priv(indio_dev);
	int ret;
	u8 addr;
	s16 val16;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return adis_single_conversion(indio_dev, chan,
				ADIS16240_ERROR_ACTIVE, val);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			if (chan->channel == 0) {
				*val = 4;
				*val2 = 880000; /* 4.88 mV */
				return IIO_VAL_INT_PLUS_MICRO;
			}
			return -EINVAL;
		case IIO_TEMP:
			*val = 244; /* 0.244 C */
			*val2 = 0;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_ACCEL:
			*val = 0;
			*val2 = IIO_G_TO_M_S_2(51400); /* 51.4 mg */
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_PEAK_SCALE:
		*val = 0;
		*val2 = IIO_G_TO_M_S_2(51400); /* 51.4 mg */
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_OFFSET:
		*val = 25000 / 244 - 0x133; /* 25 C = 0x133 */
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16240_addresses[chan->scan_index][0];
		ret = adis_read_reg_16(st, addr, &val16);
		if (ret)
			return ret;
		*val = sign_extend32(val16, 9);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_PEAK:
		addr = adis16240_addresses[chan->scan_index][1];
		ret = adis_read_reg_16(st, addr, &val16);
		if (ret)
			return ret;
		*val = sign_extend32(val16, 9);
		return IIO_VAL_INT;
	}
	return -EINVAL;
}