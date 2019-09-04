#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {int pwr_in_suspend; int /*<<< orphan*/ * if_ops; } ;
struct wl12xx_sdio_glue {TYPE_4__* core; int /*<<< orphan*/ * dev; } ;
struct sdio_func {int num; int /*<<< orphan*/  dev; TYPE_2__* card; } ;
struct sdio_device_id {int dummy; } ;
struct resource {int start; int flags; char* name; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int mmc_pm_flag_t ;
struct TYPE_11__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_12__ {TYPE_3__ dev; } ;
struct TYPE_9__ {scalar_t__ sdio_vsn; } ;
struct TYPE_10__ {TYPE_1__ cccr; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_IRQ ; 
 int MMC_PM_KEEP_POWER ; 
 int /*<<< orphan*/  MMC_QUIRK_BLKSZ_FOR_BYTE_MODE ; 
 int /*<<< orphan*/  MMC_QUIRK_LENIENT_FN0 ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 scalar_t__ SDIO_SDIO_REV_3_00 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 int irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int platform_device_add (TYPE_4__*) ; 
 int platform_device_add_data (TYPE_4__*,struct wlcore_platdev_data*,int) ; 
 int platform_device_add_resources (TYPE_4__*,struct resource*,int /*<<< orphan*/ ) ; 
 TYPE_4__* platform_device_alloc (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_4__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int sdio_get_host_pm_caps (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_ops ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct wl12xx_sdio_glue*) ; 
 int wlcore_probe_of (int /*<<< orphan*/ *,int*,struct wlcore_platdev_data*) ; 

__attribute__((used)) static int wl1271_probe(struct sdio_func *func,
				  const struct sdio_device_id *id)
{
	struct wlcore_platdev_data *pdev_data;
	struct wl12xx_sdio_glue *glue;
	struct resource res[1];
	mmc_pm_flag_t mmcflags;
	int ret = -ENOMEM;
	int irq;
	const char *chip_family;

	/* We are only able to handle the wlan function */
	if (func->num != 0x02)
		return -ENODEV;

	pdev_data = devm_kzalloc(&func->dev, sizeof(*pdev_data), GFP_KERNEL);
	if (!pdev_data)
		return -ENOMEM;

	pdev_data->if_ops = &sdio_ops;

	glue = devm_kzalloc(&func->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		return -ENOMEM;

	glue->dev = &func->dev;

	/* Grab access to FN0 for ELP reg. */
	func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

	/* Use block mode for transferring over one block size of data */
	func->card->quirks |= MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;

	ret = wlcore_probe_of(&func->dev, &irq, pdev_data);
	if (ret)
		goto out;

	/* if sdio can keep power while host is suspended, enable wow */
	mmcflags = sdio_get_host_pm_caps(func);
	dev_dbg(glue->dev, "sdio PM caps = 0x%x\n", mmcflags);

	if (mmcflags & MMC_PM_KEEP_POWER)
		pdev_data->pwr_in_suspend = true;

	sdio_set_drvdata(func, glue);

	/* Tell PM core that we don't need the card to be powered now */
	pm_runtime_put_noidle(&func->dev);

	/*
	 * Due to a hardware bug, we can't differentiate wl18xx from
	 * wl12xx, because both report the same device ID.  The only
	 * way to differentiate is by checking the SDIO revision,
	 * which is 3.00 on the wl18xx chips.
	 */
	if (func->card->cccr.sdio_vsn == SDIO_SDIO_REV_3_00)
		chip_family = "wl18xx";
	else
		chip_family = "wl12xx";

	glue->core = platform_device_alloc(chip_family, PLATFORM_DEVID_AUTO);
	if (!glue->core) {
		dev_err(glue->dev, "can't allocate platform_device");
		ret = -ENOMEM;
		goto out;
	}

	glue->core->dev.parent = &func->dev;

	memset(res, 0x00, sizeof(res));

	res[0].start = irq;
	res[0].flags = IORESOURCE_IRQ |
		       irqd_get_trigger_type(irq_get_irq_data(irq));
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
		dev_err(glue->dev, "can't add platform device\n");
		goto out_dev_put;
	}
	return 0;

out_dev_put:
	platform_device_put(glue->core);

out:
	return ret;
}