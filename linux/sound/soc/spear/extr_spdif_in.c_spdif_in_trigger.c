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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;
struct spdif_in_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  (* reset_perip ) () ;scalar_t__ io_base; TYPE_1__ saved_params; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ SPDIF_IN_CTRL ; 
 int SPDIF_IN_ENB ; 
 scalar_t__ SPDIF_IN_IRQ_MASK ; 
 int SPDIF_IN_SAMPLE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct spdif_in_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spdif_in_configure (struct spdif_in_dev*) ; 
 int /*<<< orphan*/  spdif_in_format (struct spdif_in_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spdif_in_trigger(struct snd_pcm_substream *substream, int cmd,
		struct snd_soc_dai *dai)
{
	struct spdif_in_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 ctrl;
	int ret = 0;

	if (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
		return -EINVAL;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		clk_enable(host->clk);
		spdif_in_configure(host);
		spdif_in_format(host, host->saved_params.format);

		ctrl = readl(host->io_base + SPDIF_IN_CTRL);
		ctrl |= SPDIF_IN_SAMPLE | SPDIF_IN_ENB;
		writel(ctrl, host->io_base + SPDIF_IN_CTRL);
		writel(0xF, host->io_base + SPDIF_IN_IRQ_MASK);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ctrl = readl(host->io_base + SPDIF_IN_CTRL);
		ctrl &= ~(SPDIF_IN_SAMPLE | SPDIF_IN_ENB);
		writel(ctrl, host->io_base + SPDIF_IN_CTRL);
		writel(0x0, host->io_base + SPDIF_IN_IRQ_MASK);

		if (host->reset_perip)
			host->reset_perip();
		clk_disable(host->clk);
		break;

	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}