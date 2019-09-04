#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* parent; } ;
struct iio_dev {TYPE_1__ dev; int /*<<< orphan*/  modes; void* num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {struct ad7746_platform_data* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct ad7746_platform_data {int exclvl; scalar_t__ excb_inv_en; scalar_t__ excb_en; scalar_t__ exca_inv_en; scalar_t__ exca_en; } ;
struct ad7746_chip_info {int capdac_set; struct i2c_client* client; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned char AD7746_EXCSETUP_EXCA ; 
 unsigned char AD7746_EXCSETUP_EXCB ; 
 unsigned char AD7746_EXCSETUP_EXCLVL (int) ; 
 unsigned char AD7746_EXCSETUP_NEXCA ; 
 unsigned char AD7746_EXCSETUP_NEXCB ; 
 int /*<<< orphan*/  AD7746_REG_EXC_SETUP ; 
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  ad7746_channels ; 
 int /*<<< orphan*/  ad7746_info ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned char) ; 
 struct ad7746_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7746_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ad7746_platform_data *pdata = client->dev.platform_data;
	struct ad7746_chip_info *chip;
	struct iio_dev *indio_dev;
	unsigned char regval = 0;
	int ret = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);
	mutex_init(&chip->lock);
	/* this is only used for device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	chip->client = client;
	chip->capdac_set = -1;

	/* Establish that the iio_dev is a child of the i2c device */
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &ad7746_info;
	indio_dev->channels = ad7746_channels;
	if (id->driver_data == 7746)
		indio_dev->num_channels = ARRAY_SIZE(ad7746_channels);
	else
		indio_dev->num_channels =  ARRAY_SIZE(ad7746_channels) - 2;
	indio_dev->num_channels = ARRAY_SIZE(ad7746_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (pdata) {
		if (pdata->exca_en) {
			if (pdata->exca_inv_en)
				regval |= AD7746_EXCSETUP_NEXCA;
			else
				regval |= AD7746_EXCSETUP_EXCA;
		}

		if (pdata->excb_en) {
			if (pdata->excb_inv_en)
				regval |= AD7746_EXCSETUP_NEXCB;
			else
				regval |= AD7746_EXCSETUP_EXCB;
		}

		regval |= AD7746_EXCSETUP_EXCLVL(pdata->exclvl);
	} else {
		dev_warn(&client->dev, "No platform data? using default\n");
		regval = AD7746_EXCSETUP_EXCA | AD7746_EXCSETUP_EXCB |
			AD7746_EXCSETUP_EXCLVL(3);
	}

	ret = i2c_smbus_write_byte_data(chip->client,
					AD7746_REG_EXC_SETUP, regval);
	if (ret < 0)
		return ret;

	ret = devm_iio_device_register(indio_dev->dev.parent, indio_dev);
	if (ret)
		return ret;

	return 0;
}