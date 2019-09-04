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
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  dev; } ;
struct img_spfi_device_data {int gpio_requested; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOF_OUT_INIT_HIGH ; 
 int GPIOF_OUT_INIT_LOW ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct img_spfi_device_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct img_spfi_device_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct img_spfi_device_data*) ; 

__attribute__((used)) static int img_spfi_setup(struct spi_device *spi)
{
	int ret = -EINVAL;
	struct img_spfi_device_data *spfi_data = spi_get_ctldata(spi);

	if (!spfi_data) {
		spfi_data = kzalloc(sizeof(*spfi_data), GFP_KERNEL);
		if (!spfi_data)
			return -ENOMEM;
		spfi_data->gpio_requested = false;
		spi_set_ctldata(spi, spfi_data);
	}
	if (!spfi_data->gpio_requested) {
		ret = gpio_request_one(spi->cs_gpio,
				       (spi->mode & SPI_CS_HIGH) ?
				       GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH,
				       dev_name(&spi->dev));
		if (ret)
			dev_err(&spi->dev, "can't request chipselect gpio %d\n",
				spi->cs_gpio);
		else
			spfi_data->gpio_requested = true;
	} else {
		if (gpio_is_valid(spi->cs_gpio)) {
			int mode = ((spi->mode & SPI_CS_HIGH) ?
				    GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH);

			ret = gpio_direction_output(spi->cs_gpio, mode);
			if (ret)
				dev_err(&spi->dev, "chipselect gpio %d setup failed (%d)\n",
					spi->cs_gpio, ret);
		}
	}
	return ret;
}