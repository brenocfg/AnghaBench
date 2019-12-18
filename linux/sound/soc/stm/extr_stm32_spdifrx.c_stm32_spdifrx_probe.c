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
typedef  scalar_t__ u32 ;
struct stm32_spdifrx_data {scalar_t__ dmab; struct reset_control* ctrl_chan; struct reset_control* regmap; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap_conf; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; int /*<<< orphan*/  cs_completion; struct platform_device* pdev; } ;
struct snd_dmaengine_pcm_config {int dummy; } ;
struct reset_control {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 scalar_t__ SPDIFRX_IPIDR_NUMBER ; 
 int /*<<< orphan*/  SPDIFRX_VERR_MAJ_MASK ; 
 int /*<<< orphan*/  SPDIFRX_VERR_MIN_MASK ; 
 int /*<<< orphan*/  STM32_SPDIFRX_IDR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_VERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct stm32_spdifrx_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_regmap_init_mmio_clk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_spdifrx_data*) ; 
 struct reset_control* devm_reset_control_get_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_snd_dmaengine_pcm_register (int /*<<< orphan*/ *,struct snd_dmaengine_pcm_config const*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (struct reset_control*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_spdifrx_data*) ; 
 int regmap_read (struct reset_control*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_spdifrx_component ; 
 int /*<<< orphan*/  stm32_spdifrx_dai ; 
 int stm32_spdifrx_dma_ctrl_register (int /*<<< orphan*/ *,struct stm32_spdifrx_data*) ; 
 int /*<<< orphan*/  stm32_spdifrx_isr ; 
 int stm32_spdifrx_parse_of (struct platform_device*,struct stm32_spdifrx_data*) ; 
 struct snd_dmaengine_pcm_config stm32_spdifrx_pcm_config ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32_spdifrx_probe(struct platform_device *pdev)
{
	struct stm32_spdifrx_data *spdifrx;
	struct reset_control *rst;
	const struct snd_dmaengine_pcm_config *pcm_config = NULL;
	u32 ver, idr;
	int ret;

	spdifrx = devm_kzalloc(&pdev->dev, sizeof(*spdifrx), GFP_KERNEL);
	if (!spdifrx)
		return -ENOMEM;

	spdifrx->pdev = pdev;
	init_completion(&spdifrx->cs_completion);
	spin_lock_init(&spdifrx->lock);

	platform_set_drvdata(pdev, spdifrx);

	ret = stm32_spdifrx_parse_of(pdev, spdifrx);
	if (ret)
		return ret;

	spdifrx->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "kclk",
						    spdifrx->base,
						    spdifrx->regmap_conf);
	if (IS_ERR(spdifrx->regmap)) {
		dev_err(&pdev->dev, "Regmap init failed\n");
		return PTR_ERR(spdifrx->regmap);
	}

	ret = devm_request_irq(&pdev->dev, spdifrx->irq, stm32_spdifrx_isr, 0,
			       dev_name(&pdev->dev), spdifrx);
	if (ret) {
		dev_err(&pdev->dev, "IRQ request returned %d\n", ret);
		return ret;
	}

	rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (!IS_ERR(rst)) {
		reset_control_assert(rst);
		udelay(2);
		reset_control_deassert(rst);
	}

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &stm32_spdifrx_component,
					      stm32_spdifrx_dai,
					      ARRAY_SIZE(stm32_spdifrx_dai));
	if (ret)
		return ret;

	ret = stm32_spdifrx_dma_ctrl_register(&pdev->dev, spdifrx);
	if (ret)
		goto error;

	pcm_config = &stm32_spdifrx_pcm_config;
	ret = devm_snd_dmaengine_pcm_register(&pdev->dev, pcm_config, 0);
	if (ret) {
		dev_err(&pdev->dev, "PCM DMA register returned %d\n", ret);
		goto error;
	}

	ret = regmap_read(spdifrx->regmap, STM32_SPDIFRX_IDR, &idr);
	if (ret)
		goto error;

	if (idr == SPDIFRX_IPIDR_NUMBER) {
		ret = regmap_read(spdifrx->regmap, STM32_SPDIFRX_VERR, &ver);

		dev_dbg(&pdev->dev, "SPDIFRX version: %lu.%lu registered\n",
			FIELD_GET(SPDIFRX_VERR_MAJ_MASK, ver),
			FIELD_GET(SPDIFRX_VERR_MIN_MASK, ver));
	}

	return ret;

error:
	if (!IS_ERR(spdifrx->ctrl_chan))
		dma_release_channel(spdifrx->ctrl_chan);
	if (spdifrx->dmab)
		snd_dma_free_pages(spdifrx->dmab);

	return ret;
}