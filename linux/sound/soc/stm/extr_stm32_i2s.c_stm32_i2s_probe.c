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
struct stm32_i2s_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dai_drv; int /*<<< orphan*/  regmap_conf; int /*<<< orphan*/  base; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  lock_fd; int /*<<< orphan*/  ms_flg; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2S_CGFR_I2SMOD ; 
 int /*<<< orphan*/  I2S_HWCFGR_I2S_SUPPORT_MASK ; 
 scalar_t__ I2S_IPIDR_NUMBER ; 
 int /*<<< orphan*/  I2S_MS_NOT_SET ; 
 int /*<<< orphan*/  I2S_VERR_MAJ_MASK ; 
 int /*<<< orphan*/  I2S_VERR_MIN_MASK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_I2S_CGFR_REG ; 
 int /*<<< orphan*/  STM32_I2S_HWCFGR_REG ; 
 int /*<<< orphan*/  STM32_I2S_IPIDR_REG ; 
 int /*<<< orphan*/  STM32_I2S_VERR_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stm32_i2s_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_mmio_clk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_i2s_data*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_i2s_component ; 
 int stm32_i2s_dais_init (struct platform_device*,struct stm32_i2s_data*) ; 
 int stm32_i2s_parse_dt (struct platform_device*,struct stm32_i2s_data*) ; 
 int /*<<< orphan*/  stm32_i2s_pcm_config ; 

__attribute__((used)) static int stm32_i2s_probe(struct platform_device *pdev)
{
	struct stm32_i2s_data *i2s;
	u32 val;
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
	spin_lock_init(&i2s->irq_lock);
	platform_set_drvdata(pdev, i2s);

	ret = stm32_i2s_dais_init(pdev, i2s);
	if (ret)
		return ret;

	i2s->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "pclk",
						i2s->base, i2s->regmap_conf);
	if (IS_ERR(i2s->regmap)) {
		dev_err(&pdev->dev, "regmap init failed\n");
		return PTR_ERR(i2s->regmap);
	}

	ret = devm_snd_soc_register_component(&pdev->dev, &stm32_i2s_component,
					      i2s->dai_drv, 1);
	if (ret)
		return ret;

	ret = devm_snd_dmaengine_pcm_register(&pdev->dev,
					      &stm32_i2s_pcm_config, 0);
	if (ret)
		return ret;

	/* Set SPI/I2S in i2s mode */
	ret = regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				 I2S_CGFR_I2SMOD, I2S_CGFR_I2SMOD);
	if (ret)
		return ret;

	ret = regmap_read(i2s->regmap, STM32_I2S_IPIDR_REG, &val);
	if (ret)
		return ret;

	if (val == I2S_IPIDR_NUMBER) {
		ret = regmap_read(i2s->regmap, STM32_I2S_HWCFGR_REG, &val);
		if (ret)
			return ret;

		if (!FIELD_GET(I2S_HWCFGR_I2S_SUPPORT_MASK, val)) {
			dev_err(&pdev->dev,
				"Device does not support i2s mode\n");
			return -EPERM;
		}

		ret = regmap_read(i2s->regmap, STM32_I2S_VERR_REG, &val);

		dev_dbg(&pdev->dev, "I2S version: %lu.%lu registered\n",
			FIELD_GET(I2S_VERR_MAJ_MASK, val),
			FIELD_GET(I2S_VERR_MIN_MASK, val));
	}

	return ret;
}