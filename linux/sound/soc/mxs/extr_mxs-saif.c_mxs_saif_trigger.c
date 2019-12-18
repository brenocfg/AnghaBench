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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct mxs_saif {int ongoing; int cur_rate; int /*<<< orphan*/  state; int /*<<< orphan*/  clk; scalar_t__ base; int /*<<< orphan*/  mclk_in_use; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SAIF_CTRL_RUN ; 
 int EINVAL ; 
 scalar_t__ MXS_CLR_ADDR ; 
 int /*<<< orphan*/  MXS_SAIF_STATE_RUNNING ; 
 int /*<<< orphan*/  MXS_SAIF_STATE_STOPPED ; 
 scalar_t__ MXS_SET_ADDR ; 
 scalar_t__ SAIF_CTRL ; 
 scalar_t__ SAIF_DATA ; 
 scalar_t__ SAIF_STAT ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mxs_saif* mxs_saif_get_master (struct mxs_saif*) ; 
 struct mxs_saif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mxs_saif_trigger(struct snd_pcm_substream *substream, int cmd,
				struct snd_soc_dai *cpu_dai)
{
	struct mxs_saif *saif = snd_soc_dai_get_drvdata(cpu_dai);
	struct mxs_saif *master_saif;
	u32 delay;
	int ret;

	master_saif = mxs_saif_get_master(saif);
	if (!master_saif)
		return -EINVAL;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (saif->state == MXS_SAIF_STATE_RUNNING)
			return 0;

		dev_dbg(cpu_dai->dev, "start\n");

		ret = clk_enable(master_saif->clk);
		if (ret) {
			dev_err(saif->dev, "Failed to enable master clock\n");
			return ret;
		}

		/*
		 * If the saif's master is not itself, we also need to enable
		 * itself clk for its internal basic logic to work.
		 */
		if (saif != master_saif) {
			ret = clk_enable(saif->clk);
			if (ret) {
				dev_err(saif->dev, "Failed to enable master clock\n");
				clk_disable(master_saif->clk);
				return ret;
			}

			__raw_writel(BM_SAIF_CTRL_RUN,
				saif->base + SAIF_CTRL + MXS_SET_ADDR);
		}

		if (!master_saif->mclk_in_use)
			__raw_writel(BM_SAIF_CTRL_RUN,
				master_saif->base + SAIF_CTRL + MXS_SET_ADDR);

		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			/*
			 * write data to saif data register to trigger
			 * the transfer.
			 * For 24-bit format the 32-bit FIFO register stores
			 * only one channel, so we need to write twice.
			 * This is also safe for the other non 24-bit formats.
			 */
			__raw_writel(0, saif->base + SAIF_DATA);
			__raw_writel(0, saif->base + SAIF_DATA);
		} else {
			/*
			 * read data from saif data register to trigger
			 * the receive.
			 * For 24-bit format the 32-bit FIFO register stores
			 * only one channel, so we need to read twice.
			 * This is also safe for the other non 24-bit formats.
			 */
			__raw_readl(saif->base + SAIF_DATA);
			__raw_readl(saif->base + SAIF_DATA);
		}

		master_saif->ongoing = 1;
		saif->state = MXS_SAIF_STATE_RUNNING;

		dev_dbg(saif->dev, "CTRL 0x%x STAT 0x%x\n",
			__raw_readl(saif->base + SAIF_CTRL),
			__raw_readl(saif->base + SAIF_STAT));

		dev_dbg(master_saif->dev, "CTRL 0x%x STAT 0x%x\n",
			__raw_readl(master_saif->base + SAIF_CTRL),
			__raw_readl(master_saif->base + SAIF_STAT));
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (saif->state == MXS_SAIF_STATE_STOPPED)
			return 0;

		dev_dbg(cpu_dai->dev, "stop\n");

		/* wait a while for the current sample to complete */
		delay = USEC_PER_SEC / master_saif->cur_rate;

		if (!master_saif->mclk_in_use) {
			__raw_writel(BM_SAIF_CTRL_RUN,
				master_saif->base + SAIF_CTRL + MXS_CLR_ADDR);
			udelay(delay);
		}
		clk_disable(master_saif->clk);

		if (saif != master_saif) {
			__raw_writel(BM_SAIF_CTRL_RUN,
				saif->base + SAIF_CTRL + MXS_CLR_ADDR);
			udelay(delay);
			clk_disable(saif->clk);
		}

		master_saif->ongoing = 0;
		saif->state = MXS_SAIF_STATE_STOPPED;

		break;
	default:
		return -EINVAL;
	}

	return 0;
}