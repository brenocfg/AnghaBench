#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct s3c_pcm_info {int sclk_per_fs; void* cclk; void* pclk; TYPE_2__* dma_playback; TYPE_3__* dma_capture; void* regs; int /*<<< orphan*/  lock; TYPE_1__* dev; } ;
struct s3c_audio_pdata {int /*<<< orphan*/ * dma_filter; int /*<<< orphan*/  dma_playback; int /*<<< orphan*/  dma_capture; scalar_t__ (* cfg_gpio ) (struct platform_device*) ;} ;
struct resource {scalar_t__ start; } ;
struct TYPE_11__ {struct s3c_audio_pdata* platform_data; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/ * dma_filter_fn ;
struct TYPE_13__ {int /*<<< orphan*/  filter_data; scalar_t__ addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  filter_data; scalar_t__ addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct s3c_pcm_info*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ S3C_PCM_RXFIFO ; 
 scalar_t__ S3C_PCM_TXFIFO ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct s3c_pcm_info*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 struct s3c_pcm_info* s3c_pcm ; 
 int /*<<< orphan*/  s3c_pcm_component ; 
 int /*<<< orphan*/ * s3c_pcm_dai ; 
 TYPE_3__* s3c_pcm_stereo_in ; 
 TYPE_2__* s3c_pcm_stereo_out ; 
 int samsung_asoc_dma_platform_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct platform_device*) ; 

__attribute__((used)) static int s3c_pcm_dev_probe(struct platform_device *pdev)
{
	struct s3c_pcm_info *pcm;
	struct resource *mem_res;
	struct s3c_audio_pdata *pcm_pdata;
	dma_filter_fn filter;
	int ret;

	/* Check for valid device index */
	if ((pdev->id < 0) || pdev->id >= ARRAY_SIZE(s3c_pcm)) {
		dev_err(&pdev->dev, "id %d out of range\n", pdev->id);
		return -EINVAL;
	}

	pcm_pdata = pdev->dev.platform_data;

	if (pcm_pdata && pcm_pdata->cfg_gpio && pcm_pdata->cfg_gpio(pdev)) {
		dev_err(&pdev->dev, "Unable to configure gpio\n");
		return -EINVAL;
	}

	pcm = &s3c_pcm[pdev->id];
	pcm->dev = &pdev->dev;

	spin_lock_init(&pcm->lock);

	/* Default is 128fs */
	pcm->sclk_per_fs = 128;

	mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pcm->regs = devm_ioremap_resource(&pdev->dev, mem_res);
	if (IS_ERR(pcm->regs))
		return PTR_ERR(pcm->regs);

	pcm->cclk = devm_clk_get(&pdev->dev, "audio-bus");
	if (IS_ERR(pcm->cclk)) {
		dev_err(&pdev->dev, "failed to get audio-bus clock\n");
		return PTR_ERR(pcm->cclk);
	}
	ret = clk_prepare_enable(pcm->cclk);
	if (ret)
		return ret;

	/* record our pcm structure for later use in the callbacks */
	dev_set_drvdata(&pdev->dev, pcm);

	pcm->pclk = devm_clk_get(&pdev->dev, "pcm");
	if (IS_ERR(pcm->pclk)) {
		dev_err(&pdev->dev, "failed to get pcm clock\n");
		ret = PTR_ERR(pcm->pclk);
		goto err_dis_cclk;
	}
	ret = clk_prepare_enable(pcm->pclk);
	if (ret)
		goto err_dis_cclk;

	s3c_pcm_stereo_in[pdev->id].addr = mem_res->start + S3C_PCM_RXFIFO;
	s3c_pcm_stereo_out[pdev->id].addr = mem_res->start + S3C_PCM_TXFIFO;

	filter = NULL;
	if (pcm_pdata) {
		s3c_pcm_stereo_in[pdev->id].filter_data = pcm_pdata->dma_capture;
		s3c_pcm_stereo_out[pdev->id].filter_data = pcm_pdata->dma_playback;
		filter = pcm_pdata->dma_filter;
	}

	pcm->dma_capture = &s3c_pcm_stereo_in[pdev->id];
	pcm->dma_playback = &s3c_pcm_stereo_out[pdev->id];

	ret = samsung_asoc_dma_platform_register(&pdev->dev, filter,
						 NULL, NULL, NULL);
	if (ret) {
		dev_err(&pdev->dev, "failed to get register DMA: %d\n", ret);
		goto err_dis_pclk;
	}

	pm_runtime_enable(&pdev->dev);

	ret = devm_snd_soc_register_component(&pdev->dev, &s3c_pcm_component,
					 &s3c_pcm_dai[pdev->id], 1);
	if (ret != 0) {
		dev_err(&pdev->dev, "failed to get register DAI: %d\n", ret);
		goto err_dis_pm;
	}

	return 0;

err_dis_pm:
	pm_runtime_disable(&pdev->dev);
err_dis_pclk:
	clk_disable_unprepare(pcm->pclk);
err_dis_cclk:
	clk_disable_unprepare(pcm->cclk);
	return ret;
}