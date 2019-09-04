#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* parent; } ;
struct iio_dev {TYPE_1__ dev; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ platform_data; } ;
struct i2c_client {unsigned int irq; TYPE_2__ dev; } ;
struct ad7150_chip_info {struct i2c_client* client; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  ad7150_channels ; 
 int /*<<< orphan*/  ad7150_event_handler ; 
 int /*<<< orphan*/  ad7150_info ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int devm_request_threaded_irq (TYPE_2__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7150_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct ad7150_chip_info *chip;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);
	mutex_init(&chip->state_lock);
	/* this is only used for device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	chip->client = client;

	indio_dev->name = id->name;
	indio_dev->channels = ad7150_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7150_channels);
	/* Establish that the iio_dev is a child of the i2c device */
	indio_dev->dev.parent = &client->dev;

	indio_dev->info = &ad7150_info;

	indio_dev->modes = INDIO_DIRECT_MODE;

	if (client->irq) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL,
						&ad7150_event_handler,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"ad7150_irq1",
						indio_dev);
		if (ret)
			return ret;
	}

	if (client->dev.platform_data) {
		ret = devm_request_threaded_irq(&client->dev, *(unsigned int *)
						client->dev.platform_data,
						NULL,
						&ad7150_event_handler,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"ad7150_irq2",
						indio_dev);
		if (ret)
			return ret;
	}

	ret = devm_iio_device_register(indio_dev->dev.parent, indio_dev);
	if (ret)
		return ret;

	dev_info(&client->dev, "%s capacitive sensor registered,irq: %d\n",
		 id->name, client->irq);

	return 0;
}