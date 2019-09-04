#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; TYPE_1__ dev; int /*<<< orphan*/  modes; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; } ;
struct i2c_device_id {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ad7152_chip_info {int /*<<< orphan*/  state_lock; struct i2c_client* client; } ;

/* Variables and functions */
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  ad7152_channels ; 
 int /*<<< orphan*/  ad7152_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct ad7152_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7152_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret = 0;
	struct ad7152_chip_info *chip;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);
	/* this is only used for device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	chip->client = client;
	mutex_init(&chip->state_lock);

	/* Establish that the iio_dev is a child of the i2c device */
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &ad7152_info;
	indio_dev->channels = ad7152_channels;
	if (id->driver_data == 0)
		indio_dev->num_channels = ARRAY_SIZE(ad7152_channels);
	else
		indio_dev->num_channels = 2;
	indio_dev->num_channels = ARRAY_SIZE(ad7152_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = devm_iio_device_register(indio_dev->dev.parent, indio_dev);
	if (ret)
		return ret;

	dev_err(&client->dev, "%s capacitive sensor registered\n", id->name);

	return 0;
}