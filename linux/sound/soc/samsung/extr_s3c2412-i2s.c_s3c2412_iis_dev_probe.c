#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s3c_audio_pdata {int /*<<< orphan*/  dma_filter; int /*<<< orphan*/  dma_capture; int /*<<< orphan*/  dma_playback; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  filter_data; scalar_t__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  filter_data; scalar_t__ addr; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ S3C2412_IISRXD ; 
 scalar_t__ S3C2412_IISTXD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct s3c_audio_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 TYPE_3__ s3c2412_i2s ; 
 int /*<<< orphan*/  s3c2412_i2s_component ; 
 int /*<<< orphan*/  s3c2412_i2s_dai ; 
 TYPE_2__ s3c2412_i2s_pcm_stereo_in ; 
 TYPE_1__ s3c2412_i2s_pcm_stereo_out ; 
 int s3c_i2sv2_register_component (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int samsung_asoc_dma_platform_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c2412_iis_dev_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct resource *res;
	struct s3c_audio_pdata *pdata = dev_get_platdata(&pdev->dev);

	if (!pdata) {
		dev_err(&pdev->dev, "missing platform data");
		return -ENXIO;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	s3c2412_i2s.regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(s3c2412_i2s.regs))
		return PTR_ERR(s3c2412_i2s.regs);

	s3c2412_i2s_pcm_stereo_out.addr = res->start + S3C2412_IISTXD;
	s3c2412_i2s_pcm_stereo_out.filter_data = pdata->dma_playback;
	s3c2412_i2s_pcm_stereo_in.addr = res->start + S3C2412_IISRXD;
	s3c2412_i2s_pcm_stereo_in.filter_data = pdata->dma_capture;

	ret = samsung_asoc_dma_platform_register(&pdev->dev,
						 pdata->dma_filter,
						 "tx", "rx", NULL);
	if (ret) {
		pr_err("failed to register the DMA: %d\n", ret);
		return ret;
	}

	ret = s3c_i2sv2_register_component(&pdev->dev, -1,
					   &s3c2412_i2s_component,
					   &s3c2412_i2s_dai);
	if (ret)
		pr_err("failed to register the dai\n");

	return ret;
}