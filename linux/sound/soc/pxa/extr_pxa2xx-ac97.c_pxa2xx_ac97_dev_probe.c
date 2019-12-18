#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* platform_data; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
struct ac97_controller {int dummy; } ;
struct TYPE_5__ {void** codec_pdata; } ;
typedef  TYPE_1__ pxa2xx_audio_ops_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_SLOTS_AVAILABLE_ALL ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (struct ac97_controller*) ; 
 int PTR_ERR (struct ac97_controller*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int devm_snd_soc_register_component (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ac97_controller*) ; 
 int pxa2xx_ac97_hw_probe (struct platform_device*) ; 
 int /*<<< orphan*/  pxa2xx_ac97_ops ; 
 int /*<<< orphan*/  pxa_ac97_component ; 
 int /*<<< orphan*/  pxa_ac97_dai_driver ; 
 struct ac97_controller* snd_ac97_controller_register (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int pxa2xx_ac97_dev_probe(struct platform_device *pdev)
{
	int ret;
	struct ac97_controller *ctrl;
	pxa2xx_audio_ops_t *pdata = pdev->dev.platform_data;
	void **codecs_pdata;

	if (pdev->id != -1) {
		dev_err(&pdev->dev, "PXA2xx has only one AC97 port.\n");
		return -ENXIO;
	}

	ret = pxa2xx_ac97_hw_probe(pdev);
	if (ret) {
		dev_err(&pdev->dev, "PXA2xx AC97 hw probe error (%d)\n", ret);
		return ret;
	}

	codecs_pdata = pdata ? pdata->codec_pdata : NULL;
	ctrl = snd_ac97_controller_register(&pxa2xx_ac97_ops, &pdev->dev,
					    AC97_SLOTS_AVAILABLE_ALL,
					    codecs_pdata);
	if (IS_ERR(ctrl))
		return PTR_ERR(ctrl);

	platform_set_drvdata(pdev, ctrl);
	/* Punt most of the init to the SoC probe; we may need the machine
	 * driver to do interesting things with the clocking to get us up
	 * and running.
	 */
	return devm_snd_soc_register_component(&pdev->dev, &pxa_ac97_component,
					  pxa_ac97_dai_driver, ARRAY_SIZE(pxa_ac97_dai_driver));
}