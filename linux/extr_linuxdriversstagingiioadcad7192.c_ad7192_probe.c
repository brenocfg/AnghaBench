#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; void* num_channels; void* channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct ad7192_state {int int_vref_mv; int devid; void* avdd; void* dvdd; int /*<<< orphan*/  sd; int /*<<< orphan*/  lock; } ;
struct ad7192_platform_data {int vref_mv; } ;
struct TYPE_4__ {int driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENODEV ; 
 int ENOMEM ; 
#define  ID_AD7193 128 
 int ID_AD7195 ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* ad7192_channels ; 
 int /*<<< orphan*/  ad7192_info ; 
 int ad7192_setup (struct ad7192_state*,struct ad7192_platform_data const*) ; 
 int /*<<< orphan*/  ad7192_sigma_delta_info ; 
 void* ad7193_channels ; 
 int /*<<< orphan*/  ad7195_info ; 
 int /*<<< orphan*/  ad_sd_cleanup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  ad_sd_init (int /*<<< orphan*/ *,struct iio_dev*,struct spi_device*,int /*<<< orphan*/ *) ; 
 int ad_sd_setup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ad7192_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad7192_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int regulator_get_voltage (void*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7192_probe(struct spi_device *spi)
{
	const struct ad7192_platform_data *pdata = dev_get_platdata(&spi->dev);
	struct ad7192_state *st;
	struct iio_dev *indio_dev;
	int ret, voltage_uv = 0;

	if (!pdata) {
		dev_err(&spi->dev, "no platform data?\n");
		return -ENODEV;
	}

	if (!spi->irq) {
		dev_err(&spi->dev, "no IRQ?\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);

	st->avdd = devm_regulator_get(&spi->dev, "avdd");
	if (IS_ERR(st->avdd))
		return PTR_ERR(st->avdd);

	ret = regulator_enable(st->avdd);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified AVdd supply\n");
		return ret;
	}

	st->dvdd = devm_regulator_get(&spi->dev, "dvdd");
	if (IS_ERR(st->dvdd)) {
		ret = PTR_ERR(st->dvdd);
		goto error_disable_avdd;
	}

	ret = regulator_enable(st->dvdd);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified DVdd supply\n");
		goto error_disable_avdd;
	}

	voltage_uv = regulator_get_voltage(st->avdd);

	if (pdata->vref_mv)
		st->int_vref_mv = pdata->vref_mv;
	else if (voltage_uv)
		st->int_vref_mv = voltage_uv / 1000;
	else
		dev_warn(&spi->dev, "reference voltage undefined\n");

	spi_set_drvdata(spi, indio_dev);
	st->devid = spi_get_device_id(spi)->driver_data;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	switch (st->devid) {
	case ID_AD7193:
		indio_dev->channels = ad7193_channels;
		indio_dev->num_channels = ARRAY_SIZE(ad7193_channels);
		break;
	default:
		indio_dev->channels = ad7192_channels;
		indio_dev->num_channels = ARRAY_SIZE(ad7192_channels);
		break;
	}

	if (st->devid == ID_AD7195)
		indio_dev->info = &ad7195_info;
	else
		indio_dev->info = &ad7192_info;

	ad_sd_init(&st->sd, indio_dev, spi, &ad7192_sigma_delta_info);

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	if (ret)
		goto error_disable_dvdd;

	ret = ad7192_setup(st, pdata);
	if (ret)
		goto error_remove_trigger;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto error_remove_trigger;
	return 0;

error_remove_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_dvdd:
	regulator_disable(st->dvdd);
error_disable_avdd:
	regulator_disable(st->avdd);

	return ret;
}