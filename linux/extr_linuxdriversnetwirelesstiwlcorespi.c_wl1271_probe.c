#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {TYPE_1__* family; int /*<<< orphan*/ * if_ops; } ;
struct wl12xx_spi_glue {TYPE_3__* core; int /*<<< orphan*/ * dev; int /*<<< orphan*/  reg; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct resource {int flags; char* name; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  res ;
struct TYPE_9__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {TYPE_2__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int platform_device_add (TYPE_3__*) ; 
 int platform_device_add_data (TYPE_3__*,struct wlcore_platdev_data*,int) ; 
 int platform_device_add_resources (TYPE_3__*,struct resource*,int /*<<< orphan*/ ) ; 
 TYPE_3__* platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_3__*) ; 
 int /*<<< orphan*/  spi_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct wl12xx_spi_glue*) ; 
 int spi_setup (struct spi_device*) ; 
 int wlcore_probe_of (struct spi_device*,struct wl12xx_spi_glue*,struct wlcore_platdev_data*) ; 

__attribute__((used)) static int wl1271_probe(struct spi_device *spi)
{
	struct wl12xx_spi_glue *glue;
	struct wlcore_platdev_data *pdev_data;
	struct resource res[1];
	int ret;

	pdev_data = devm_kzalloc(&spi->dev, sizeof(*pdev_data), GFP_KERNEL);
	if (!pdev_data)
		return -ENOMEM;

	pdev_data->if_ops = &spi_ops;

	glue = devm_kzalloc(&spi->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue) {
		dev_err(&spi->dev, "can't allocate glue\n");
		return -ENOMEM;
	}

	glue->dev = &spi->dev;

	spi_set_drvdata(spi, glue);

	/* This is the only SPI value that we need to set here, the rest
	 * comes from the board-peripherals file */
	spi->bits_per_word = 32;

	glue->reg = devm_regulator_get(&spi->dev, "vwlan");
	if (PTR_ERR(glue->reg) == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (IS_ERR(glue->reg)) {
		dev_err(glue->dev, "can't get regulator\n");
		return PTR_ERR(glue->reg);
	}

	ret = wlcore_probe_of(spi, glue, pdev_data);
	if (ret) {
		dev_err(glue->dev,
			"can't get device tree parameters (%d)\n", ret);
		return ret;
	}

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(glue->dev, "spi_setup failed\n");
		return ret;
	}

	glue->core = platform_device_alloc(pdev_data->family->name,
					   PLATFORM_DEVID_AUTO);
	if (!glue->core) {
		dev_err(glue->dev, "can't allocate platform_device\n");
		return -ENOMEM;
	}

	glue->core->dev.parent = &spi->dev;

	memset(res, 0x00, sizeof(res));

	res[0].start = spi->irq;
	res[0].flags = IORESOURCE_IRQ | irq_get_trigger_type(spi->irq);
	res[0].name = "irq";

	ret = platform_device_add_resources(glue->core, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(glue->dev, "can't add resources\n");
		goto out_dev_put;
	}

	ret = platform_device_add_data(glue->core, pdev_data,
				       sizeof(*pdev_data));
	if (ret) {
		dev_err(glue->dev, "can't add platform data\n");
		goto out_dev_put;
	}

	ret = platform_device_add(glue->core);
	if (ret) {
		dev_err(glue->dev, "can't register platform device\n");
		goto out_dev_put;
	}

	return 0;

out_dev_put:
	platform_device_put(glue->core);
	return ret;
}