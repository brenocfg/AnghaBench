#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mtk_base_afe {int memif_size; int irqs_size; int (* runtime_resume ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  runtime_suspend; int /*<<< orphan*/  reg_back_up_list_num; int /*<<< orphan*/ * reg_back_up_list; int /*<<< orphan*/  irq_fs; int /*<<< orphan*/  memif_fs; int /*<<< orphan*/ * mtk_afe_hardware; TYPE_2__* memif; TYPE_1__* irqs; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  base_addr; struct mt8173_afe_private* platform_priv; } ;
struct mt8173_afe_private {int dummy; } ;
struct TYPE_4__ {int irq_usage; int const_irq; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int irq_occupyed; int /*<<< orphan*/ * irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MT8173_AFE_IRQ_NUM ; 
 int MT8173_AFE_MEMIF_NUM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_mmio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * irq_data ; 
 int /*<<< orphan*/ * memif_data ; 
 int /*<<< orphan*/ * mt8173_afe_backup_list ; 
 int /*<<< orphan*/  mt8173_afe_hardware ; 
 int /*<<< orphan*/  mt8173_afe_hdmi_dai_component ; 
 int /*<<< orphan*/ * mt8173_afe_hdmi_dais ; 
 int mt8173_afe_init_audio_clk (struct mtk_base_afe*) ; 
 int /*<<< orphan*/  mt8173_afe_irq_handler ; 
 int /*<<< orphan*/  mt8173_afe_pcm_dai_component ; 
 int /*<<< orphan*/ * mt8173_afe_pcm_dais ; 
 int /*<<< orphan*/  mt8173_afe_regmap_config ; 
 int mt8173_afe_runtime_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt8173_afe_runtime_suspend ; 
 int /*<<< orphan*/  mt8173_irq_fs ; 
 int /*<<< orphan*/  mt8173_memif_fs ; 
 int /*<<< orphan*/  mtk_afe_pcm_platform ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_base_afe*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enabled (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt8173_afe_pcm_dev_probe(struct platform_device *pdev)
{
	int ret, i;
	int irq_id;
	struct mtk_base_afe *afe;
	struct mt8173_afe_private *afe_priv;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(33));
	if (ret)
		return ret;

	afe = devm_kzalloc(&pdev->dev, sizeof(*afe), GFP_KERNEL);
	if (!afe)
		return -ENOMEM;

	afe->platform_priv = devm_kzalloc(&pdev->dev, sizeof(*afe_priv),
					  GFP_KERNEL);
	afe_priv = afe->platform_priv;
	if (!afe_priv)
		return -ENOMEM;

	afe->dev = &pdev->dev;

	irq_id = platform_get_irq(pdev, 0);
	if (irq_id <= 0)
		return irq_id < 0 ? irq_id : -ENXIO;
	ret = devm_request_irq(afe->dev, irq_id, mt8173_afe_irq_handler,
			       0, "Afe_ISR_Handle", (void *)afe);
	if (ret) {
		dev_err(afe->dev, "could not request_irq\n");
		return ret;
	}

	afe->base_addr = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(afe->base_addr))
		return PTR_ERR(afe->base_addr);

	afe->regmap = devm_regmap_init_mmio(&pdev->dev, afe->base_addr,
		&mt8173_afe_regmap_config);
	if (IS_ERR(afe->regmap))
		return PTR_ERR(afe->regmap);

	/* initial audio related clock */
	ret = mt8173_afe_init_audio_clk(afe);
	if (ret) {
		dev_err(afe->dev, "mt8173_afe_init_audio_clk fail\n");
		return ret;
	}

	/* memif % irq initialize*/
	afe->memif_size = MT8173_AFE_MEMIF_NUM;
	afe->memif = devm_kcalloc(afe->dev, afe->memif_size,
				  sizeof(*afe->memif), GFP_KERNEL);
	if (!afe->memif)
		return -ENOMEM;

	afe->irqs_size = MT8173_AFE_IRQ_NUM;
	afe->irqs = devm_kcalloc(afe->dev, afe->irqs_size,
				 sizeof(*afe->irqs), GFP_KERNEL);
	if (!afe->irqs)
		return -ENOMEM;

	for (i = 0; i < afe->irqs_size; i++) {
		afe->memif[i].data = &memif_data[i];
		afe->irqs[i].irq_data = &irq_data[i];
		afe->irqs[i].irq_occupyed = true;
		afe->memif[i].irq_usage = i;
		afe->memif[i].const_irq = 1;
	}

	afe->mtk_afe_hardware = &mt8173_afe_hardware;
	afe->memif_fs = mt8173_memif_fs;
	afe->irq_fs = mt8173_irq_fs;

	platform_set_drvdata(pdev, afe);

	pm_runtime_enable(&pdev->dev);
	if (!pm_runtime_enabled(&pdev->dev)) {
		ret = mt8173_afe_runtime_resume(&pdev->dev);
		if (ret)
			goto err_pm_disable;
	}

	afe->reg_back_up_list = mt8173_afe_backup_list;
	afe->reg_back_up_list_num = ARRAY_SIZE(mt8173_afe_backup_list);
	afe->runtime_resume = mt8173_afe_runtime_resume;
	afe->runtime_suspend = mt8173_afe_runtime_suspend;

	ret = devm_snd_soc_register_component(&pdev->dev,
					 &mtk_afe_pcm_platform,
					 NULL, 0);
	if (ret)
		goto err_pm_disable;

	ret = devm_snd_soc_register_component(&pdev->dev,
					 &mt8173_afe_pcm_dai_component,
					 mt8173_afe_pcm_dais,
					 ARRAY_SIZE(mt8173_afe_pcm_dais));
	if (ret)
		goto err_pm_disable;

	ret = devm_snd_soc_register_component(&pdev->dev,
					 &mt8173_afe_hdmi_dai_component,
					 mt8173_afe_hdmi_dais,
					 ARRAY_SIZE(mt8173_afe_hdmi_dais));
	if (ret)
		goto err_pm_disable;

	dev_info(&pdev->dev, "MT8173 AFE driver initialized.\n");
	return 0;

err_pm_disable:
	pm_runtime_disable(&pdev->dev);
	return ret;
}