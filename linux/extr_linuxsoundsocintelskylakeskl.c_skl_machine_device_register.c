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
struct snd_soc_acpi_mach {scalar_t__ pdata; int /*<<< orphan*/  drv_name; } ;
struct skl {struct platform_device* i2s_dev; struct snd_soc_acpi_mach* mach; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,scalar_t__) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct hdac_bus* skl_to_bus (struct skl*) ; 

__attribute__((used)) static int skl_machine_device_register(struct skl *skl)
{
	struct hdac_bus *bus = skl_to_bus(skl);
	struct snd_soc_acpi_mach *mach = skl->mach;
	struct platform_device *pdev;
	int ret;

	pdev = platform_device_alloc(mach->drv_name, -1);
	if (pdev == NULL) {
		dev_err(bus->dev, "platform device alloc failed\n");
		return -EIO;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		dev_err(bus->dev, "failed to add machine device\n");
		platform_device_put(pdev);
		return -EIO;
	}

	if (mach->pdata)
		dev_set_drvdata(&pdev->dev, mach->pdata);

	skl->i2s_dev = pdev;

	return 0;
}