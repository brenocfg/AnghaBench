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
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7192_state {int /*<<< orphan*/  mode; int /*<<< orphan*/  sd; int /*<<< orphan*/  gpocon; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7192_GPOCON_BPDSW ; 
 int /*<<< orphan*/  AD7192_MODE_ACX ; 
#define  AD7192_REG_GPOCON 129 
#define  AD7192_REG_MODE 128 
 int EINVAL ; 
 int /*<<< orphan*/  ad_sd_write_reg (int /*<<< orphan*/ *,int const,int,int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad7192_state* iio_priv (struct iio_dev*) ; 
 int strtobool (char const*,int*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7192_set(struct device *dev,
			  struct device_attribute *attr,
			  const char *buf,
			  size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7192_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret;
	bool val;

	ret = strtobool(buf, &val);
	if (ret < 0)
		return ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;

	switch ((u32)this_attr->address) {
	case AD7192_REG_GPOCON:
		if (val)
			st->gpocon |= AD7192_GPOCON_BPDSW;
		else
			st->gpocon &= ~AD7192_GPOCON_BPDSW;

		ad_sd_write_reg(&st->sd, AD7192_REG_GPOCON, 1, st->gpocon);
		break;
	case AD7192_REG_MODE:
		if (val)
			st->mode |= AD7192_MODE_ACX;
		else
			st->mode &= ~AD7192_MODE_ACX;

		ad_sd_write_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
		break;
	default:
		ret = -EINVAL;
	}

	iio_device_release_direct_mode(indio_dev);

	return ret ? ret : len;
}