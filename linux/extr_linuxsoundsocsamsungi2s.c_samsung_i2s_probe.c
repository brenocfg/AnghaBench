#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct samsung_i2s_dai_data {int quirks; int /*<<< orphan*/  i2s_variant_regs; } ;
struct TYPE_22__ {int quirks; int idma_addr; } ;
struct s3c_audio_pdata {scalar_t__ (* cfg_gpio ) (struct platform_device*) ;int /*<<< orphan*/  dma_filter; int /*<<< orphan*/  dma_play_sec; TYPE_2__ type; int /*<<< orphan*/  dma_capture; int /*<<< orphan*/  dma_playback; } ;
struct resource {int start; } ;
struct TYPE_26__ {struct device_node* of_node; struct s3c_audio_pdata* platform_data; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_25__ {int channels_max; } ;
struct TYPE_20__ {TYPE_5__ playback; } ;
struct TYPE_21__ {int addr; } ;
struct TYPE_23__ {int addr; char* chan_name; int addr_width; int /*<<< orphan*/  filter_data; } ;
struct TYPE_24__ {int addr; char* chan_name; int addr_width; int /*<<< orphan*/  filter_data; } ;
struct i2s_dai {int quirks; int /*<<< orphan*/  clk; int /*<<< orphan*/ * clk_table; int /*<<< orphan*/  op_clk; TYPE_13__ i2s_dai_drv; int /*<<< orphan*/  filter; struct i2s_dai* sec_dai; struct i2s_dai* pri_dai; TYPE_1__ idma_playback; int /*<<< orphan*/  addr; TYPE_3__ dma_playback; int /*<<< orphan*/  variant_regs; int /*<<< orphan*/  spinlock; int /*<<< orphan*/ * lock; TYPE_4__ dma_capture; } ;
struct device_node {int dummy; } ;
struct TYPE_19__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 size_t CLK_I2S_RCLK_SRC ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int I2SRXD ; 
 int I2STXD ; 
 int I2STXDS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int QUIRK_PRI_6CHAN ; 
 int QUIRK_SEC_DAI ; 
 int QUIRK_SUPPORTS_IDMA ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_parent (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_6__*,struct i2s_dai*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_6__*,struct resource*) ; 
 int devm_snd_soc_register_component (TYPE_6__*,int /*<<< orphan*/ *,TYPE_13__*,int) ; 
 struct i2s_dai* i2s_alloc_dai (struct platform_device*,struct samsung_i2s_dai_data const*,int) ; 
 int i2s_register_clock_provider (struct platform_device*) ; 
 struct samsung_i2s_dai_data* of_device_get_match_data (TYPE_6__*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 TYPE_10__* platform_get_device_id (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_6__*) ; 
 int samsung_asoc_dma_platform_register (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  samsung_i2s_component ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct platform_device*) ; 

__attribute__((used)) static int samsung_i2s_probe(struct platform_device *pdev)
{
	struct i2s_dai *pri_dai, *sec_dai = NULL;
	struct s3c_audio_pdata *i2s_pdata = pdev->dev.platform_data;
	struct resource *res;
	u32 regs_base, quirks = 0, idma_addr = 0;
	struct device_node *np = pdev->dev.of_node;
	const struct samsung_i2s_dai_data *i2s_dai_data;
	int ret;

	if (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node)
		i2s_dai_data = of_device_get_match_data(&pdev->dev);
	else
		i2s_dai_data = (struct samsung_i2s_dai_data *)
				platform_get_device_id(pdev)->driver_data;

	pri_dai = i2s_alloc_dai(pdev, i2s_dai_data, false);
	if (!pri_dai) {
		dev_err(&pdev->dev, "Unable to alloc I2S_pri\n");
		return -ENOMEM;
	}

	spin_lock_init(&pri_dai->spinlock);
	pri_dai->lock = &pri_dai->spinlock;

	if (!np) {
		if (i2s_pdata == NULL) {
			dev_err(&pdev->dev, "Can't work without s3c_audio_pdata\n");
			return -EINVAL;
		}

		pri_dai->dma_playback.filter_data = i2s_pdata->dma_playback;
		pri_dai->dma_capture.filter_data = i2s_pdata->dma_capture;
		pri_dai->filter = i2s_pdata->dma_filter;

		quirks = i2s_pdata->type.quirks;
		idma_addr = i2s_pdata->type.idma_addr;
	} else {
		quirks = i2s_dai_data->quirks;
		if (of_property_read_u32(np, "samsung,idma-addr",
					 &idma_addr)) {
			if (quirks & QUIRK_SUPPORTS_IDMA) {
				dev_info(&pdev->dev, "idma address is not"\
						"specified");
			}
		}
	}
	quirks &= ~(QUIRK_SEC_DAI | QUIRK_SUPPORTS_IDMA);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pri_dai->addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pri_dai->addr))
		return PTR_ERR(pri_dai->addr);

	regs_base = res->start;

	pri_dai->clk = devm_clk_get(&pdev->dev, "iis");
	if (IS_ERR(pri_dai->clk)) {
		dev_err(&pdev->dev, "Failed to get iis clock\n");
		return PTR_ERR(pri_dai->clk);
	}

	ret = clk_prepare_enable(pri_dai->clk);
	if (ret != 0) {
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		return ret;
	}
	pri_dai->dma_playback.addr = regs_base + I2STXD;
	pri_dai->dma_capture.addr = regs_base + I2SRXD;
	pri_dai->dma_playback.chan_name = "tx";
	pri_dai->dma_capture.chan_name = "rx";
	pri_dai->dma_playback.addr_width = 4;
	pri_dai->dma_capture.addr_width = 4;
	pri_dai->quirks = quirks;
	pri_dai->variant_regs = i2s_dai_data->i2s_variant_regs;

	if (quirks & QUIRK_PRI_6CHAN)
		pri_dai->i2s_dai_drv.playback.channels_max = 6;

	ret = samsung_asoc_dma_platform_register(&pdev->dev, pri_dai->filter,
						 NULL, NULL);
	if (ret < 0)
		goto err_disable_clk;

	ret = devm_snd_soc_register_component(&pdev->dev,
					&samsung_i2s_component,
					&pri_dai->i2s_dai_drv, 1);
	if (ret < 0)
		goto err_disable_clk;

	if (quirks & QUIRK_SEC_DAI) {
		sec_dai = i2s_alloc_dai(pdev, i2s_dai_data, true);
		if (!sec_dai) {
			dev_err(&pdev->dev, "Unable to alloc I2S_sec\n");
			ret = -ENOMEM;
			goto err_disable_clk;
		}

		sec_dai->lock = &pri_dai->spinlock;
		sec_dai->variant_regs = pri_dai->variant_regs;
		sec_dai->dma_playback.addr = regs_base + I2STXDS;
		sec_dai->dma_playback.chan_name = "tx-sec";

		if (!np) {
			sec_dai->dma_playback.filter_data = i2s_pdata->dma_play_sec;
			sec_dai->filter = i2s_pdata->dma_filter;
		}

		sec_dai->dma_playback.addr_width = 4;
		sec_dai->addr = pri_dai->addr;
		sec_dai->clk = pri_dai->clk;
		sec_dai->quirks = quirks;
		sec_dai->idma_playback.addr = idma_addr;
		sec_dai->pri_dai = pri_dai;
		pri_dai->sec_dai = sec_dai;

		ret = samsung_asoc_dma_platform_register(&pdev->dev,
					sec_dai->filter, "tx-sec", NULL);
		if (ret < 0)
			goto err_disable_clk;

		ret = devm_snd_soc_register_component(&pdev->dev,
						&samsung_i2s_component,
						&sec_dai->i2s_dai_drv, 1);
		if (ret < 0)
			goto err_disable_clk;
	}

	if (i2s_pdata && i2s_pdata->cfg_gpio && i2s_pdata->cfg_gpio(pdev)) {
		dev_err(&pdev->dev, "Unable to configure gpio\n");
		ret = -EINVAL;
		goto err_disable_clk;
	}

	dev_set_drvdata(&pdev->dev, pri_dai);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = i2s_register_clock_provider(pdev);
	if (ret < 0)
		goto err_disable_pm;

	pri_dai->op_clk = clk_get_parent(pri_dai->clk_table[CLK_I2S_RCLK_SRC]);

	return 0;

err_disable_pm:
	pm_runtime_disable(&pdev->dev);
err_disable_clk:
	clk_disable_unprepare(pri_dai->clk);
	return ret;
}