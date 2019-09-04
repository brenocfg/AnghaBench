#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stm32_sai_sub_data {uintptr_t id; int /*<<< orphan*/  cpu_dai_drv; TYPE_7__* pdata; int /*<<< orphan*/  ctrl_lock; struct platform_device* pdev; } ;
struct snd_dmaengine_pcm_config {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 TYPE_7__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct stm32_sai_sub_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_sai_sub_data*) ; 
 int devm_snd_dmaengine_pcm_register (TYPE_1__*,struct snd_dmaengine_pcm_config const*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  stm32_component ; 
 int /*<<< orphan*/  stm32_sai_isr ; 
 struct snd_dmaengine_pcm_config stm32_sai_pcm_config ; 
 struct snd_dmaengine_pcm_config stm32_sai_pcm_config_spdif ; 
 int stm32_sai_sub_dais_init (struct platform_device*,struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  stm32_sai_sub_ids ; 
 int stm32_sai_sub_parse_of (struct platform_device*,struct stm32_sai_sub_data*) ; 

__attribute__((used)) static int stm32_sai_sub_probe(struct platform_device *pdev)
{
	struct stm32_sai_sub_data *sai;
	const struct of_device_id *of_id;
	const struct snd_dmaengine_pcm_config *conf = &stm32_sai_pcm_config;
	int ret;

	sai = devm_kzalloc(&pdev->dev, sizeof(*sai), GFP_KERNEL);
	if (!sai)
		return -ENOMEM;

	of_id = of_match_device(stm32_sai_sub_ids, &pdev->dev);
	if (!of_id)
		return -EINVAL;
	sai->id = (uintptr_t)of_id->data;

	sai->pdev = pdev;
	mutex_init(&sai->ctrl_lock);
	platform_set_drvdata(pdev, sai);

	sai->pdata = dev_get_drvdata(pdev->dev.parent);
	if (!sai->pdata) {
		dev_err(&pdev->dev, "Parent device data not available\n");
		return -EINVAL;
	}

	ret = stm32_sai_sub_parse_of(pdev, sai);
	if (ret)
		return ret;

	ret = stm32_sai_sub_dais_init(pdev, sai);
	if (ret)
		return ret;

	ret = devm_request_irq(&pdev->dev, sai->pdata->irq, stm32_sai_isr,
			       IRQF_SHARED, dev_name(&pdev->dev), sai);
	if (ret) {
		dev_err(&pdev->dev, "IRQ request returned %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&pdev->dev, &stm32_component,
					      sai->cpu_dai_drv, 1);
	if (ret)
		return ret;

	if (STM_SAI_PROTOCOL_IS_SPDIF(sai))
		conf = &stm32_sai_pcm_config_spdif;

	ret = devm_snd_dmaengine_pcm_register(&pdev->dev, conf, 0);
	if (ret) {
		dev_err(&pdev->dev, "Could not register pcm dma\n");
		return ret;
	}

	return 0;
}