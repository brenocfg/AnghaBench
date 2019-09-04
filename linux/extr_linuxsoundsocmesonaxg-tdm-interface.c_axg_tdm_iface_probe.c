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
struct snd_soc_dai_driver {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct axg_tdm_iface {int /*<<< orphan*/ * mclk; int /*<<< orphan*/ * lrclk; int /*<<< orphan*/ * sclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axg_tdm_iface_component_drv ; 
 int /*<<< orphan*/ * axg_tdm_iface_dai_drv ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct snd_soc_dai_driver* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct axg_tdm_iface* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,struct snd_soc_dai_driver*,int) ; 
 int /*<<< orphan*/  memcpy (struct snd_soc_dai_driver*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct axg_tdm_iface*) ; 

__attribute__((used)) static int axg_tdm_iface_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct snd_soc_dai_driver *dai_drv;
	struct axg_tdm_iface *iface;
	int ret, i;

	iface = devm_kzalloc(dev, sizeof(*iface), GFP_KERNEL);
	if (!iface)
		return -ENOMEM;
	platform_set_drvdata(pdev, iface);

	/*
	 * Duplicate dai driver: depending on the slot masks configuration
	 * We'll change the number of channel provided by DAI stream, so dpcm
	 * channel merge can be done properly
	 */
	dai_drv = devm_kcalloc(dev, ARRAY_SIZE(axg_tdm_iface_dai_drv),
			       sizeof(*dai_drv), GFP_KERNEL);
	if (!dai_drv)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(axg_tdm_iface_dai_drv); i++)
		memcpy(&dai_drv[i], &axg_tdm_iface_dai_drv[i],
		       sizeof(*dai_drv));

	/* Bit clock provided on the pad */
	iface->sclk = devm_clk_get(dev, "sclk");
	if (IS_ERR(iface->sclk)) {
		ret = PTR_ERR(iface->sclk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get sclk: %d\n", ret);
		return ret;
	}

	/* Sample clock provided on the pad */
	iface->lrclk = devm_clk_get(dev, "lrclk");
	if (IS_ERR(iface->lrclk)) {
		ret = PTR_ERR(iface->lrclk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get lrclk: %d\n", ret);
		return ret;
	}

	/*
	 * mclk maybe be missing when the cpu dai is in slave mode and
	 * the codec does not require it to provide a master clock.
	 * At this point, ignore the error if mclk is missing. We'll
	 * throw an error if the cpu dai is master and mclk is missing
	 */
	iface->mclk = devm_clk_get(dev, "mclk");
	if (IS_ERR(iface->mclk)) {
		ret = PTR_ERR(iface->mclk);
		if (ret == -ENOENT) {
			iface->mclk = NULL;
		} else {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to get mclk: %d\n", ret);
			return ret;
		}
	}

	return devm_snd_soc_register_component(dev,
					&axg_tdm_iface_component_drv, dai_drv,
					ARRAY_SIZE(axg_tdm_iface_dai_drv));
}