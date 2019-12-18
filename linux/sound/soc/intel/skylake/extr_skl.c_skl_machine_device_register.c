#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  codec_mask; int /*<<< orphan*/  platform; } ;
struct snd_soc_acpi_mach {TYPE_1__ mach_params; int /*<<< orphan*/  drv_name; } ;
struct skl_dev {struct platform_device* i2s_dev; struct snd_soc_acpi_mach* mach; } ;
struct platform_device {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  codec_mask; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,void const*,int) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct hdac_bus* skl_to_bus (struct skl_dev*) ; 

__attribute__((used)) static int skl_machine_device_register(struct skl_dev *skl)
{
	struct snd_soc_acpi_mach *mach = skl->mach;
	struct hdac_bus *bus = skl_to_bus(skl);
	struct platform_device *pdev;
	int ret;

	pdev = platform_device_alloc(mach->drv_name, -1);
	if (pdev == NULL) {
		dev_err(bus->dev, "platform device alloc failed\n");
		return -EIO;
	}

	mach->mach_params.platform = dev_name(bus->dev);
	mach->mach_params.codec_mask = bus->codec_mask;

	ret = platform_device_add_data(pdev, (const void *)mach, sizeof(*mach));
	if (ret) {
		dev_err(bus->dev, "failed to add machine device platform data\n");
		platform_device_put(pdev);
		return ret;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		dev_err(bus->dev, "failed to add machine device\n");
		platform_device_put(pdev);
		return -EIO;
	}


	skl->i2s_dev = pdev;

	return 0;
}