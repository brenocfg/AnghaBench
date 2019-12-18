#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/ * platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct audio_drv_data {int /*<<< orphan*/  asic_type; int /*<<< orphan*/  acp_mmio; int /*<<< orphan*/ * capture_i2sbt_stream; int /*<<< orphan*/ * play_i2sbt_stream; int /*<<< orphan*/ * capture_i2ssp_stream; int /*<<< orphan*/ * play_i2ssp_stream; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_asoc_platform ; 
 int acp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct audio_drv_data*) ; 
 struct audio_drv_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_irq_handler ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 

__attribute__((used)) static int acp_audio_probe(struct platform_device *pdev)
{
	int status;
	struct audio_drv_data *audio_drv_data;
	struct resource *res;
	const u32 *pdata = pdev->dev.platform_data;

	if (!pdata) {
		dev_err(&pdev->dev, "Missing platform data\n");
		return -ENODEV;
	}

	audio_drv_data = devm_kzalloc(&pdev->dev, sizeof(struct audio_drv_data),
				      GFP_KERNEL);
	if (!audio_drv_data)
		return -ENOMEM;

	audio_drv_data->acp_mmio = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(audio_drv_data->acp_mmio))
		return PTR_ERR(audio_drv_data->acp_mmio);

	/*
	 * The following members gets populated in device 'open'
	 * function. Till then interrupts are disabled in 'acp_init'
	 * and device doesn't generate any interrupts.
	 */

	audio_drv_data->play_i2ssp_stream = NULL;
	audio_drv_data->capture_i2ssp_stream = NULL;
	audio_drv_data->play_i2sbt_stream = NULL;
	audio_drv_data->capture_i2sbt_stream = NULL;

	audio_drv_data->asic_type =  *pdata;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(&pdev->dev, "IORESOURCE_IRQ FAILED\n");
		return -ENODEV;
	}

	status = devm_request_irq(&pdev->dev, res->start, dma_irq_handler,
				  0, "ACP_IRQ", &pdev->dev);
	if (status) {
		dev_err(&pdev->dev, "ACP IRQ request failed\n");
		return status;
	}

	dev_set_drvdata(&pdev->dev, audio_drv_data);

	/* Initialize the ACP */
	status = acp_init(audio_drv_data->acp_mmio, audio_drv_data->asic_type);
	if (status) {
		dev_err(&pdev->dev, "ACP Init failed status:%d\n", status);
		return status;
	}

	status = devm_snd_soc_register_component(&pdev->dev,
						 &acp_asoc_platform, NULL, 0);
	if (status != 0) {
		dev_err(&pdev->dev, "Fail to register ALSA platform device\n");
		return status;
	}

	pm_runtime_set_autosuspend_delay(&pdev->dev, 10000);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	return status;
}