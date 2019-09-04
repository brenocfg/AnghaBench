#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_4__ {struct ep93xx_rtc* platform_data; int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct ep93xx_rtc {int /*<<< orphan*/  rtc; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct ep93xx_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_rtc_ops ; 
 int /*<<< orphan*/  ep93xx_rtc_sysfs_files ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ep93xx_rtc*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ep93xx_rtc_probe(struct platform_device *pdev)
{
	struct ep93xx_rtc *ep93xx_rtc;
	struct resource *res;
	int err;

	ep93xx_rtc = devm_kzalloc(&pdev->dev, sizeof(*ep93xx_rtc), GFP_KERNEL);
	if (!ep93xx_rtc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ep93xx_rtc->mmio_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ep93xx_rtc->mmio_base))
		return PTR_ERR(ep93xx_rtc->mmio_base);

	pdev->dev.platform_data = ep93xx_rtc;
	platform_set_drvdata(pdev, ep93xx_rtc);

	ep93xx_rtc->rtc = devm_rtc_device_register(&pdev->dev,
				pdev->name, &ep93xx_rtc_ops, THIS_MODULE);
	if (IS_ERR(ep93xx_rtc->rtc)) {
		err = PTR_ERR(ep93xx_rtc->rtc);
		goto exit;
	}

	err = sysfs_create_group(&pdev->dev.kobj, &ep93xx_rtc_sysfs_files);
	if (err)
		goto exit;

	return 0;

exit:
	pdev->dev.platform_data = NULL;
	return err;
}