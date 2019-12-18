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
typedef  int u32 ;
struct xlnx_pcm_drv_data {int mm2s_presence; int mm2s_irq; int s2mm_presence; int s2mm_irq; scalar_t__ axi_clk; scalar_t__ mmio; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int AUD_CFG_MM2S_MASK ; 
 int AUD_CFG_S2MM_MASK ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ XLNX_AUD_CORE_CONFIG ; 
 scalar_t__ XLNX_MM2S_OFFSET ; 
 scalar_t__ XLNX_S2MM_OFFSET ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct xlnx_pcm_drv_data*) ; 
 scalar_t__ devm_clk_get (struct device*,char*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct xlnx_pcm_drv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  xlnx_asoc_component ; 
 int /*<<< orphan*/  xlnx_formatter_disable_irqs (scalar_t__,int /*<<< orphan*/ ) ; 
 int xlnx_formatter_pcm_reset (scalar_t__) ; 
 int /*<<< orphan*/  xlnx_mm2s_irq_handler ; 
 int /*<<< orphan*/  xlnx_s2mm_irq_handler ; 

__attribute__((used)) static int xlnx_formatter_pcm_probe(struct platform_device *pdev)
{
	int ret;
	u32 val;
	struct xlnx_pcm_drv_data *aud_drv_data;
	struct resource *res;
	struct device *dev = &pdev->dev;

	aud_drv_data = devm_kzalloc(dev, sizeof(*aud_drv_data), GFP_KERNEL);
	if (!aud_drv_data)
		return -ENOMEM;

	aud_drv_data->axi_clk = devm_clk_get(dev, "s_axi_lite_aclk");
	if (IS_ERR(aud_drv_data->axi_clk)) {
		ret = PTR_ERR(aud_drv_data->axi_clk);
		dev_err(dev, "failed to get s_axi_lite_aclk(%d)\n", ret);
		return ret;
	}
	ret = clk_prepare_enable(aud_drv_data->axi_clk);
	if (ret) {
		dev_err(dev,
			"failed to enable s_axi_lite_aclk(%d)\n", ret);
		return ret;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "audio formatter node:addr to resource failed\n");
		ret = -ENXIO;
		goto clk_err;
	}
	aud_drv_data->mmio = devm_ioremap_resource(dev, res);
	if (IS_ERR(aud_drv_data->mmio)) {
		dev_err(dev, "audio formatter ioremap failed\n");
		ret = PTR_ERR(aud_drv_data->mmio);
		goto clk_err;
	}

	val = readl(aud_drv_data->mmio + XLNX_AUD_CORE_CONFIG);
	if (val & AUD_CFG_MM2S_MASK) {
		aud_drv_data->mm2s_presence = true;
		ret = xlnx_formatter_pcm_reset(aud_drv_data->mmio +
					       XLNX_MM2S_OFFSET);
		if (ret) {
			dev_err(dev, "audio formatter reset failed\n");
			goto clk_err;
		}
		xlnx_formatter_disable_irqs(aud_drv_data->mmio +
					    XLNX_MM2S_OFFSET,
					    SNDRV_PCM_STREAM_PLAYBACK);

		aud_drv_data->mm2s_irq = platform_get_irq_byname(pdev,
								 "irq_mm2s");
		if (aud_drv_data->mm2s_irq < 0) {
			ret = aud_drv_data->mm2s_irq;
			goto clk_err;
		}
		ret = devm_request_irq(dev, aud_drv_data->mm2s_irq,
				       xlnx_mm2s_irq_handler, 0,
				       "xlnx_formatter_pcm_mm2s_irq", dev);
		if (ret) {
			dev_err(dev, "xlnx audio mm2s irq request failed\n");
			goto clk_err;
		}
	}
	if (val & AUD_CFG_S2MM_MASK) {
		aud_drv_data->s2mm_presence = true;
		ret = xlnx_formatter_pcm_reset(aud_drv_data->mmio +
					       XLNX_S2MM_OFFSET);
		if (ret) {
			dev_err(dev, "audio formatter reset failed\n");
			goto clk_err;
		}
		xlnx_formatter_disable_irqs(aud_drv_data->mmio +
					    XLNX_S2MM_OFFSET,
					    SNDRV_PCM_STREAM_CAPTURE);

		aud_drv_data->s2mm_irq = platform_get_irq_byname(pdev,
								 "irq_s2mm");
		if (aud_drv_data->s2mm_irq < 0) {
			ret = aud_drv_data->s2mm_irq;
			goto clk_err;
		}
		ret = devm_request_irq(dev, aud_drv_data->s2mm_irq,
				       xlnx_s2mm_irq_handler, 0,
				       "xlnx_formatter_pcm_s2mm_irq",
				       dev);
		if (ret) {
			dev_err(dev, "xlnx audio s2mm irq request failed\n");
			goto clk_err;
		}
	}

	dev_set_drvdata(dev, aud_drv_data);

	ret = devm_snd_soc_register_component(dev, &xlnx_asoc_component,
					      NULL, 0);
	if (ret) {
		dev_err(dev, "pcm platform device register failed\n");
		goto clk_err;
	}

	return 0;

clk_err:
	clk_disable_unprepare(aud_drv_data->axi_clk);
	return ret;
}