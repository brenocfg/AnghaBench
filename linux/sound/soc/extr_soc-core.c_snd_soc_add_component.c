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
struct snd_soc_dai_driver {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; } ;
struct snd_soc_component_driver {scalar_t__ endianness; } ;
struct snd_soc_component {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  convert_endianness_formats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  snd_soc_component_add (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_cleanup (struct snd_soc_component*) ; 
 int snd_soc_component_initialize (struct snd_soc_component*,struct snd_soc_component_driver const*,struct device*) ; 
 int snd_soc_register_dais (struct snd_soc_component*,struct snd_soc_dai_driver*,int) ; 
 int /*<<< orphan*/  snd_soc_try_rebind_card () ; 

int snd_soc_add_component(struct device *dev,
			struct snd_soc_component *component,
			const struct snd_soc_component_driver *component_driver,
			struct snd_soc_dai_driver *dai_drv,
			int num_dai)
{
	int ret;
	int i;

	ret = snd_soc_component_initialize(component, component_driver, dev);
	if (ret)
		goto err_free;

	if (component_driver->endianness) {
		for (i = 0; i < num_dai; i++) {
			convert_endianness_formats(&dai_drv[i].playback);
			convert_endianness_formats(&dai_drv[i].capture);
		}
	}

	ret = snd_soc_register_dais(component, dai_drv, num_dai);
	if (ret < 0) {
		dev_err(dev, "ASoC: Failed to register DAIs: %d\n", ret);
		goto err_cleanup;
	}

	snd_soc_component_add(component);
	snd_soc_try_rebind_card();

	return 0;

err_cleanup:
	snd_soc_component_cleanup(component);
err_free:
	return ret;
}