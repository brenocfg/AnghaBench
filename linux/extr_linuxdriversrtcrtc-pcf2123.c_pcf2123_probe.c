#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {struct pcf2123_plat_data* platform_data; } ;
struct spi_device {int max_speed_hz; TYPE_4__ dev; } ;
struct rtc_time {int dummy; } ;
struct rtc_device {int dummy; } ;
struct pcf2123_plat_data {TYPE_2__* regs; struct rtc_device* rtc; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_20__ {TYPE_1__ driver; } ;
struct TYPE_18__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  store; int /*<<< orphan*/  show; TYPE_3__ attr; } ;
struct TYPE_17__ {TYPE_10__ attr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int) ; 
 int device_create_file (TYPE_4__*,TYPE_10__*) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_4__*,TYPE_10__*) ; 
 struct pcf2123_plat_data* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 struct rtc_device* devm_rtc_device_register (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__ pcf2123_driver ; 
 int pcf2123_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  pcf2123_rtc_ops ; 
 int pcf2123_rtc_read_time (TYPE_4__*,struct rtc_time*) ; 
 int /*<<< orphan*/  pcf2123_show ; 
 int /*<<< orphan*/  pcf2123_store ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_3__*) ; 

__attribute__((used)) static int pcf2123_probe(struct spi_device *spi)
{
	struct rtc_device *rtc;
	struct rtc_time tm;
	struct pcf2123_plat_data *pdata;
	int ret, i;

	pdata = devm_kzalloc(&spi->dev, sizeof(struct pcf2123_plat_data),
				GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	spi->dev.platform_data = pdata;

	ret = pcf2123_rtc_read_time(&spi->dev, &tm);
	if (ret < 0) {
		ret = pcf2123_reset(&spi->dev);
		if (ret < 0) {
			dev_err(&spi->dev, "chip not found\n");
			goto kfree_exit;
		}
	}

	dev_info(&spi->dev, "spiclk %u KHz.\n",
			(spi->max_speed_hz + 500) / 1000);

	/* Finalize the initialization */
	rtc = devm_rtc_device_register(&spi->dev, pcf2123_driver.driver.name,
			&pcf2123_rtc_ops, THIS_MODULE);

	if (IS_ERR(rtc)) {
		dev_err(&spi->dev, "failed to register.\n");
		ret = PTR_ERR(rtc);
		goto kfree_exit;
	}

	pdata->rtc = rtc;

	for (i = 0; i < 16; i++) {
		sysfs_attr_init(&pdata->regs[i].attr.attr);
		sprintf(pdata->regs[i].name, "%1x", i);
		pdata->regs[i].attr.attr.mode = S_IRUGO | S_IWUSR;
		pdata->regs[i].attr.attr.name = pdata->regs[i].name;
		pdata->regs[i].attr.show = pcf2123_show;
		pdata->regs[i].attr.store = pcf2123_store;
		ret = device_create_file(&spi->dev, &pdata->regs[i].attr);
		if (ret) {
			dev_err(&spi->dev, "Unable to create sysfs %s\n",
				pdata->regs[i].name);
			goto sysfs_exit;
		}
	}

	return 0;

sysfs_exit:
	for (i--; i >= 0; i--)
		device_remove_file(&spi->dev, &pdata->regs[i].attr);

kfree_exit:
	spi->dev.platform_data = NULL;
	return ret;
}