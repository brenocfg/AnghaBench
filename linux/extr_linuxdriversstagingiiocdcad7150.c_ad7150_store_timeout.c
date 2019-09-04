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
typedef  void* u8 ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7150_chip_info {int /*<<< orphan*/  state_lock; void*** thresh_timeout; void*** mag_timeout; } ;
typedef  int ssize_t ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_EVENT_CODE_EXTRACT_CHAN (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_DIR (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_TYPE (int /*<<< orphan*/ ) ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_TYPE_MAG_ADAPTIVE 129 
#define  IIO_EV_TYPE_THRESH_ADAPTIVE 128 
 int ad7150_write_event_params (struct iio_dev*,int,int,int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtou8 (char const*,int,void**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7150_store_timeout(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7150_chip_info *chip = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int chan = IIO_EVENT_CODE_EXTRACT_CHAN(this_attr->address);
	enum iio_event_direction dir;
	enum iio_event_type type;
	int rising;
	u8 data;
	int ret;

	type = IIO_EVENT_CODE_EXTRACT_TYPE(this_attr->address);
	dir = IIO_EVENT_CODE_EXTRACT_DIR(this_attr->address);
	rising = (dir == IIO_EV_DIR_RISING);

	ret = kstrtou8(buf, 10, &data);
	if (ret < 0)
		return ret;

	mutex_lock(&chip->state_lock);
	switch (type) {
	case IIO_EV_TYPE_MAG_ADAPTIVE:
		chip->mag_timeout[rising][chan] = data;
		break;
	case IIO_EV_TYPE_THRESH_ADAPTIVE:
		chip->thresh_timeout[rising][chan] = data;
		break;
	default:
		ret = -EINVAL;
		goto error_ret;
	}

	ret = ad7150_write_event_params(indio_dev, chan, type, dir);
error_ret:
	mutex_unlock(&chip->state_lock);

	if (ret < 0)
		return ret;

	return len;
}