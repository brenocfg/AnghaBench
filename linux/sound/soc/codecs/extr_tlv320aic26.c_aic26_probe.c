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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct aic26 {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC26_REG_AUDIO_CTRL3 ; 
 int /*<<< orphan*/  AIC26_REG_POWER_CTRL ; 
 int /*<<< orphan*/  AIC26_REG_RESET ; 
 int /*<<< orphan*/  dev_attr_keyclick ; 
 struct aic26* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic26_probe(struct snd_soc_component *component)
{
	struct aic26 *aic26 = dev_get_drvdata(component->dev);
	int ret, reg;

	aic26->component = component;

	/* Reset the codec to power on defaults */
	snd_soc_component_write(component, AIC26_REG_RESET, 0xBB00);

	/* Power up CODEC */
	snd_soc_component_write(component, AIC26_REG_POWER_CTRL, 0);

	/* Audio Control 3 (master mode, fsref rate) */
	reg = snd_soc_component_read32(component, AIC26_REG_AUDIO_CTRL3);
	reg &= ~0xf800;
	reg |= 0x0800; /* set master mode */
	snd_soc_component_write(component, AIC26_REG_AUDIO_CTRL3, reg);

	/* Register the sysfs files for debugging */
	/* Create SysFS files */
	ret = device_create_file(component->dev, &dev_attr_keyclick);
	if (ret)
		dev_info(component->dev, "error creating sysfs files\n");

	return 0;
}