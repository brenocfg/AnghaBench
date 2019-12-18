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
struct snd_soc_dai_driver {int dummy; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_component {TYPE_1__* driver; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  non_legacy_dai_naming; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_dais (struct snd_soc_component*) ; 
 struct snd_soc_dai* soc_add_dai (struct snd_soc_component*,struct snd_soc_dai_driver*,int) ; 

__attribute__((used)) static int snd_soc_register_dais(struct snd_soc_component *component,
				 struct snd_soc_dai_driver *dai_drv,
				 size_t count)
{
	struct device *dev = component->dev;
	struct snd_soc_dai *dai;
	unsigned int i;
	int ret;

	dev_dbg(dev, "ASoC: dai register %s #%zu\n", dev_name(dev), count);

	for (i = 0; i < count; i++) {

		dai = soc_add_dai(component, dai_drv + i, count == 1 &&
				  !component->driver->non_legacy_dai_naming);
		if (dai == NULL) {
			ret = -ENOMEM;
			goto err;
		}
	}

	return 0;

err:
	snd_soc_unregister_dais(component);

	return ret;
}