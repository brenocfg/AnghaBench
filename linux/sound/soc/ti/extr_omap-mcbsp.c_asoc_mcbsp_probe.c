#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; } ;
struct omap_mcbsp_platform_data {int buffer_size; int reg_size; int /*<<< orphan*/  force_ick_on; } ;
struct omap_mcbsp {struct omap_mcbsp_platform_data* pdata; TYPE_3__* dev; int /*<<< orphan*/  id; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {void* formats; } ;
struct TYPE_11__ {void* formats; } ;
struct TYPE_14__ {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* SNDRV_PCM_FMTBIT_S16_LE ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct omap_mcbsp_platform_data* dev_get_platdata (TYPE_3__*) ; 
 void* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (struct omap_mcbsp_platform_data*,int /*<<< orphan*/ ,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  omap_mcbsp_component ; 
 TYPE_4__ omap_mcbsp_dai ; 
 int omap_mcbsp_init (struct platform_device*) ; 
 int /*<<< orphan*/  omap_mcbsp_of_match ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_mcbsp*) ; 
 int sdma_pcm_platform_register (TYPE_3__*,char*,char*) ; 

__attribute__((used)) static int asoc_mcbsp_probe(struct platform_device *pdev)
{
	struct omap_mcbsp_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct omap_mcbsp *mcbsp;
	const struct of_device_id *match;
	int ret;

	match = of_match_device(omap_mcbsp_of_match, &pdev->dev);
	if (match) {
		struct device_node *node = pdev->dev.of_node;
		struct omap_mcbsp_platform_data *pdata_quirk = pdata;
		int buffer_size;

		pdata = devm_kzalloc(&pdev->dev,
				     sizeof(struct omap_mcbsp_platform_data),
				     GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;

		memcpy(pdata, match->data, sizeof(*pdata));
		if (!of_property_read_u32(node, "ti,buffer-size", &buffer_size))
			pdata->buffer_size = buffer_size;
		if (pdata_quirk)
			pdata->force_ick_on = pdata_quirk->force_ick_on;
	} else if (!pdata) {
		dev_err(&pdev->dev, "missing platform data.\n");
		return -EINVAL;
	}
	mcbsp = devm_kzalloc(&pdev->dev, sizeof(struct omap_mcbsp), GFP_KERNEL);
	if (!mcbsp)
		return -ENOMEM;

	mcbsp->id = pdev->id;
	mcbsp->pdata = pdata;
	mcbsp->dev = &pdev->dev;
	platform_set_drvdata(pdev, mcbsp);

	ret = omap_mcbsp_init(pdev);
	if (ret)
		return ret;

	if (mcbsp->pdata->reg_size == 2) {
		omap_mcbsp_dai.playback.formats = SNDRV_PCM_FMTBIT_S16_LE;
		omap_mcbsp_dai.capture.formats = SNDRV_PCM_FMTBIT_S16_LE;
	}

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &omap_mcbsp_component,
					      &omap_mcbsp_dai, 1);
	if (ret)
		return ret;

	return sdma_pcm_platform_register(&pdev->dev, "tx", "rx");
}