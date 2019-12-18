#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct stm32_sai_sub_data {uintptr_t id; TYPE_1__ cpu_dai_drv; TYPE_10__* pdata; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  ctrl_lock; struct platform_device* pdev; } ;
struct snd_dmaengine_pcm_config {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ STM_SAI_IS_PLAYBACK (struct stm32_sai_sub_data*) ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 TYPE_10__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct stm32_sai_sub_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_sai_sub_data*) ; 
 int devm_snd_dmaengine_pcm_register (TYPE_3__*,struct snd_dmaengine_pcm_config const*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_component ; 
 TYPE_1__ stm32_sai_capture_dai ; 
 int /*<<< orphan*/  stm32_sai_isr ; 
 struct snd_dmaengine_pcm_config stm32_sai_pcm_config ; 
 struct snd_dmaengine_pcm_config stm32_sai_pcm_config_spdif ; 
 TYPE_1__ stm32_sai_playback_dai ; 
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
	spin_lock_init(&sai->irq_lock);
	platform_set_drvdata(pdev, sai);

	sai->pdata = dev_get_drvdata(pdev->dev.parent);
	if (!sai->pdata) {
		dev_err(&pdev->dev, "Parent device data not available\n");
		return -EINVAL;
	}

	ret = stm32_sai_sub_parse_of(pdev, sai);
	if (ret)
		return ret;

	if (STM_SAI_IS_PLAYBACK(sai))
		sai->cpu_dai_drv = stm32_sai_playback_dai;
	else
		sai->cpu_dai_drv = stm32_sai_capture_dai;
	sai->cpu_dai_drv.name = dev_name(&pdev->dev);

	ret = devm_request_irq(&pdev->dev, sai->pdata->irq, stm32_sai_isr,
			       IRQF_SHARED, dev_name(&pdev->dev), sai);
	if (ret) {
		dev_err(&pdev->dev, "IRQ request returned %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&pdev->dev, &stm32_component,
					      &sai->cpu_dai_drv, 1);
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