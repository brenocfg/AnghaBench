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
struct spi_device {int max_speed_hz; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; } ;
struct ad2s90_state {struct spi_device* sdev; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  ad2s90_chan ; 
 int /*<<< orphan*/  ad2s90_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct ad2s90_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ad2s90_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct ad2s90_state *st;
	int ret = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	mutex_init(&st->lock);
	st->sdev = spi;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ad2s90_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = &ad2s90_chan;
	indio_dev->num_channels = 1;
	indio_dev->name = spi_get_device_id(spi)->name;

	ret = devm_iio_device_register(indio_dev->dev.parent, indio_dev);
	if (ret)
		return ret;

	/* need 600ns between CS and the first falling edge of SCLK */
	spi->max_speed_hz = 830000;
	spi->mode = SPI_MODE_3;
	ret = spi_setup(spi);

	if (ret < 0) {
		dev_err(&spi->dev, "spi_setup failed!\n");
		return ret;
	}

	return 0;
}