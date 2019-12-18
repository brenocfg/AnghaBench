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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct platform_device {size_t id; } ;
struct atmel_ssc_info {TYPE_2__* ssc; struct atmel_pcm_dma_params** dma_params; } ;
struct atmel_pcm_dma_params {TYPE_1__* mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ssc_error; int /*<<< orphan*/  ssc_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  IDR ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ) ; 
 struct atmel_ssc_info* ssc_info ; 
 int /*<<< orphan*/  ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_ssc_prepare(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct platform_device *pdev = to_platform_device(dai->dev);
	struct atmel_ssc_info *ssc_p = &ssc_info[pdev->id];
	struct atmel_pcm_dma_params *dma_params;
	int dir;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	else
		dir = 1;

	dma_params = ssc_p->dma_params[dir];

	ssc_writel(ssc_p->ssc->regs, CR, dma_params->mask->ssc_disable);
	ssc_writel(ssc_p->ssc->regs, IDR, dma_params->mask->ssc_error);

	pr_debug("%s enabled SSC_SR=0x%08x\n",
			dir ? "receive" : "transmit",
			ssc_readl(ssc_p->ssc->regs, SR));
	return 0;
}