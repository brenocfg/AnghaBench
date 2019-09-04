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
struct snd_ac97_reset_cfg {int dummy; } ;
struct snd_ac97_bus_ops {int /*<<< orphan*/  reset; int /*<<< orphan*/  warm_reset; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 struct snd_ac97_reset_cfg snd_ac97_rst_cfg ; 
 int snd_soc_ac97_parse_pinctl (struct device*,struct snd_ac97_reset_cfg*) ; 
 int /*<<< orphan*/  snd_soc_ac97_reset ; 
 int /*<<< orphan*/  snd_soc_ac97_warm_reset ; 
 int snd_soc_set_ac97_ops (struct snd_ac97_bus_ops*) ; 

int snd_soc_set_ac97_ops_of_reset(struct snd_ac97_bus_ops *ops,
		struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct snd_ac97_reset_cfg cfg;
	int ret;

	ret = snd_soc_ac97_parse_pinctl(dev, &cfg);
	if (ret)
		return ret;

	ret = snd_soc_set_ac97_ops(ops);
	if (ret)
		return ret;

	ops->warm_reset = snd_soc_ac97_warm_reset;
	ops->reset = snd_soc_ac97_reset;

	snd_ac97_rst_cfg = cfg;
	return 0;
}