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
struct spi_device {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad7816_chip_info {int* oti_data; unsigned short rdwr_pin; unsigned short convert_pin; unsigned short busy_pin; struct spi_device* spi_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AD7816_CS_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  ad7816_event_handler ; 
 int /*<<< orphan*/  ad7816_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 unsigned short* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int devm_gpio_request (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  gpio_direction_input (unsigned short) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int ad7816_probe(struct spi_device *spi_dev)
{
	struct ad7816_chip_info *chip;
	struct iio_dev *indio_dev;
	unsigned short *pins = dev_get_platdata(&spi_dev->dev);
	int ret = 0;
	int i;

	if (!pins) {
		dev_err(&spi_dev->dev, "No necessary GPIO platform data.\n");
		return -EINVAL;
	}

	indio_dev = devm_iio_device_alloc(&spi_dev->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);
	/* this is only used for device removal purposes */
	dev_set_drvdata(&spi_dev->dev, indio_dev);

	chip->spi_dev = spi_dev;
	for (i = 0; i <= AD7816_CS_MAX; i++)
		chip->oti_data[i] = 203;
	chip->rdwr_pin = pins[0];
	chip->convert_pin = pins[1];
	chip->busy_pin = pins[2];

	ret = devm_gpio_request(&spi_dev->dev, chip->rdwr_pin,
				spi_get_device_id(spi_dev)->name);
	if (ret) {
		dev_err(&spi_dev->dev, "Fail to request rdwr gpio PIN %d.\n",
			chip->rdwr_pin);
		return ret;
	}
	gpio_direction_input(chip->rdwr_pin);
	ret = devm_gpio_request(&spi_dev->dev, chip->convert_pin,
				spi_get_device_id(spi_dev)->name);
	if (ret) {
		dev_err(&spi_dev->dev, "Fail to request convert gpio PIN %d.\n",
			chip->convert_pin);
		return ret;
	}
	gpio_direction_input(chip->convert_pin);
	ret = devm_gpio_request(&spi_dev->dev, chip->busy_pin,
				spi_get_device_id(spi_dev)->name);
	if (ret) {
		dev_err(&spi_dev->dev, "Fail to request busy gpio PIN %d.\n",
			chip->busy_pin);
		return ret;
	}
	gpio_direction_input(chip->busy_pin);

	indio_dev->name = spi_get_device_id(spi_dev)->name;
	indio_dev->dev.parent = &spi_dev->dev;
	indio_dev->info = &ad7816_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (spi_dev->irq) {
		/* Only low trigger is supported in ad7816/7/8 */
		ret = devm_request_threaded_irq(&spi_dev->dev, spi_dev->irq,
						NULL,
						&ad7816_event_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		if (ret)
			return ret;
	}

	ret = devm_iio_device_register(&spi_dev->dev, indio_dev);
	if (ret)
		return ret;

	dev_info(&spi_dev->dev, "%s temperature sensor and ADC registered.\n",
		 indio_dev->name);

	return 0;
}