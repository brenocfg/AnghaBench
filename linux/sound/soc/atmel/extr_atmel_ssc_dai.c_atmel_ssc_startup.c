#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
struct platform_device {size_t id; } ;
struct atmel_ssc_info {int dir_mask; struct atmel_pcm_dma_params** dma_params; TYPE_1__* ssc; int /*<<< orphan*/  initialized; int /*<<< orphan*/  mck_rate; } ;
struct atmel_pcm_dma_params {struct snd_pcm_substream* substream; TYPE_1__* ssc; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_SWRST ; 
 int EBUSY ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FRAME_BITS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  SSC_BIT (int /*<<< orphan*/ ) ; 
 int SSC_DIR_MASK_CAPTURE ; 
 int SSC_DIR_MASK_PLAYBACK ; 
 int /*<<< orphan*/  atmel_ssc_hw_rule_rate ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int snd_pcm_hw_rule_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atmel_ssc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dai_set_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*,struct atmel_pcm_dma_params*) ; 
 struct atmel_pcm_dma_params** ssc_dma_params ; 
 struct atmel_ssc_info* ssc_info ; 
 int /*<<< orphan*/  ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_ssc_startup(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct platform_device *pdev = to_platform_device(dai->dev);
	struct atmel_ssc_info *ssc_p = &ssc_info[pdev->id];
	struct atmel_pcm_dma_params *dma_params;
	int dir, dir_mask;
	int ret;

	pr_debug("atmel_ssc_startup: SSC_SR=0x%x\n",
		ssc_readl(ssc_p->ssc->regs, SR));

	/* Enable PMC peripheral clock for this SSC */
	pr_debug("atmel_ssc_dai: Starting clock\n");
	clk_enable(ssc_p->ssc->clk);
	ssc_p->mck_rate = clk_get_rate(ssc_p->ssc->clk);

	/* Reset the SSC unless initialized to keep it in a clean state */
	if (!ssc_p->initialized)
		ssc_writel(ssc_p->ssc->regs, CR, SSC_BIT(CR_SWRST));

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		dir = 0;
		dir_mask = SSC_DIR_MASK_PLAYBACK;
	} else {
		dir = 1;
		dir_mask = SSC_DIR_MASK_CAPTURE;
	}

	ret = snd_pcm_hw_rule_add(substream->runtime, 0,
				  SNDRV_PCM_HW_PARAM_RATE,
				  atmel_ssc_hw_rule_rate,
				  ssc_p,
				  SNDRV_PCM_HW_PARAM_FRAME_BITS,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (ret < 0) {
		dev_err(dai->dev, "Failed to specify rate rule: %d\n", ret);
		return ret;
	}

	dma_params = &ssc_dma_params[pdev->id][dir];
	dma_params->ssc = ssc_p->ssc;
	dma_params->substream = substream;

	ssc_p->dma_params[dir] = dma_params;

	snd_soc_dai_set_dma_data(dai, substream, dma_params);

	if (ssc_p->dir_mask & dir_mask)
		return -EBUSY;

	ssc_p->dir_mask |= dir_mask;

	return 0;
}