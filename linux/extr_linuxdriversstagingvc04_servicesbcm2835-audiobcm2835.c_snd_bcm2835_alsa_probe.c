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
typedef  scalar_t__ u32 ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 scalar_t__ MAX_SUBSTREAMS ; 
 int bcm2835_devm_add_vchi_ctx (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int snd_add_child_devices (struct device*,scalar_t__) ; 

__attribute__((used)) static int snd_bcm2835_alsa_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	u32 numchans;
	int err;

	err = of_property_read_u32(dev->of_node, "brcm,pwm-channels",
				   &numchans);
	if (err) {
		dev_err(dev, "Failed to get DT property 'brcm,pwm-channels'");
		return err;
	}

	if (numchans == 0 || numchans > MAX_SUBSTREAMS) {
		numchans = MAX_SUBSTREAMS;
		dev_warn(dev,
			 "Illegal 'brcm,pwm-channels' value, will use %u\n",
			 numchans);
	}

	err = bcm2835_devm_add_vchi_ctx(dev);
	if (err)
		return err;

	err = snd_add_child_devices(dev, numchans);
	if (err)
		return err;

	return 0;
}