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
struct skl_dev {struct platform_device* dmic_dev; } ;
struct platform_device {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct hdac_bus* skl_to_bus (struct skl_dev*) ; 

__attribute__((used)) static int skl_dmic_device_register(struct skl_dev *skl)
{
	struct hdac_bus *bus = skl_to_bus(skl);
	struct platform_device *pdev;
	int ret;

	/* SKL has one dmic port, so allocate dmic device for this */
	pdev = platform_device_alloc("dmic-codec", -1);
	if (!pdev) {
		dev_err(bus->dev, "failed to allocate dmic device\n");
		return -ENOMEM;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		dev_err(bus->dev, "failed to add dmic device: %d\n", ret);
		platform_device_put(pdev);
		return ret;
	}
	skl->dmic_dev = pdev;

	return 0;
}