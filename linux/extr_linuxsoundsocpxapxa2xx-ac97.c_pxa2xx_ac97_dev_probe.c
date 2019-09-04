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
struct platform_device {int id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int pxa2xx_ac97_hw_probe (struct platform_device*) ; 
 int /*<<< orphan*/  pxa2xx_ac97_ops ; 
 int /*<<< orphan*/  pxa_ac97_component ; 
 int /*<<< orphan*/  pxa_ac97_dai_driver ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa2xx_ac97_dev_probe(struct platform_device *pdev)
{
	int ret;

	if (pdev->id != -1) {
		dev_err(&pdev->dev, "PXA2xx has only one AC97 port.\n");
		return -ENXIO;
	}

	ret = pxa2xx_ac97_hw_probe(pdev);
	if (ret) {
		dev_err(&pdev->dev, "PXA2xx AC97 hw probe error (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_set_ac97_ops(&pxa2xx_ac97_ops);
	if (ret != 0)
		return ret;

	/* Punt most of the init to the SoC probe; we may need the machine
	 * driver to do interesting things with the clocking to get us up
	 * and running.
	 */
	return snd_soc_register_component(&pdev->dev, &pxa_ac97_component,
					  pxa_ac97_dai_driver, ARRAY_SIZE(pxa_ac97_dai_driver));
}