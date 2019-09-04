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
struct stm32_i2s_data {int /*<<< orphan*/  pclk; int /*<<< orphan*/  i2sclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dai_drv; int /*<<< orphan*/  regmap_conf; int /*<<< orphan*/  base; int /*<<< orphan*/  lock_fd; int /*<<< orphan*/  ms_flg; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2S_CGFR_I2SMOD ; 
 int /*<<< orphan*/  I2S_MS_NOT_SET ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_I2S_CGFR_REG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct stm32_i2s_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_mmio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_i2s_data*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_i2s_component ; 
 int stm32_i2s_dais_init (struct platform_device*,struct stm32_i2s_data*) ; 
 int stm32_i2s_parse_dt (struct platform_device*,struct stm32_i2s_data*) ; 
 int /*<<< orphan*/  stm32_i2s_pcm_config ; 

__attribute__((used)) static int stm32_i2s_probe(struct platform_device *pdev)
{
	struct stm32_i2s_data *i2s;
	int ret;

	i2s = devm_kzalloc(&pdev->dev, sizeof(*i2s), GFP_KERNEL);
	if (!i2s)
		return -ENOMEM;

	ret = stm32_i2s_parse_dt(pdev, i2s);
	if (ret)
		return ret;

	i2s->pdev = pdev;
	i2s->ms_flg = I2S_MS_NOT_SET;
	spin_lock_init(&i2s->lock_fd);
	platform_set_drvdata(pdev, i2s);

	ret = stm32_i2s_dais_init(pdev, i2s);
	if (ret)
		return ret;

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, i2s->base,
					    i2s->regmap_conf);
	if (IS_ERR(i2s->regmap)) {
		dev_err(&pdev->dev, "regmap init failed\n");
		return PTR_ERR(i2s->regmap);
	}

	ret = clk_prepare_enable(i2s->pclk);
	if (ret) {
		dev_err(&pdev->dev, "Enable pclk failed: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(i2s->i2sclk);
	if (ret) {
		dev_err(&pdev->dev, "Enable i2sclk failed: %d\n", ret);
		goto err_pclk_disable;
	}

	ret = devm_snd_soc_register_component(&pdev->dev, &stm32_i2s_component,
					      i2s->dai_drv, 1);
	if (ret)
		goto err_clocks_disable;

	ret = devm_snd_dmaengine_pcm_register(&pdev->dev,
					      &stm32_i2s_pcm_config, 0);
	if (ret)
		goto err_clocks_disable;

	/* Set SPI/I2S in i2s mode */
	ret = regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				 I2S_CGFR_I2SMOD, I2S_CGFR_I2SMOD);
	if (ret)
		goto err_clocks_disable;

	return ret;

err_clocks_disable:
	clk_disable_unprepare(i2s->i2sclk);
err_pclk_disable:
	clk_disable_unprepare(i2s->pclk);

	return ret;
}