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
struct snd_dmaengine_pcm_config {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_DMAENGINE_PCM_FLAG_COMPAT ; 
 struct snd_dmaengine_pcm_config* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (int /*<<< orphan*/ *,struct snd_dmaengine_pcm_config*,int /*<<< orphan*/ ) ; 
 struct snd_dmaengine_pcm_config imx_dmaengine_pcm_config ; 

int imx_pcm_dma_init(struct platform_device *pdev, size_t size)
{
	struct snd_dmaengine_pcm_config *config;

	config = devm_kzalloc(&pdev->dev,
			sizeof(struct snd_dmaengine_pcm_config), GFP_KERNEL);
	if (!config)
		return -ENOMEM;
	*config = imx_dmaengine_pcm_config;

	return devm_snd_dmaengine_pcm_register(&pdev->dev,
		config,
		SND_DMAENGINE_PCM_FLAG_COMPAT);
}