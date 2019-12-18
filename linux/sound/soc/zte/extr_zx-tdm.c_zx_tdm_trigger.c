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
struct zx_tdm_info {int dummy; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FIFOCTRL_RX_FIFO_RST ; 
 unsigned int FIFOCTRL_TX_FIFO_RST ; 
 int /*<<< orphan*/  REG_RX_FIFO_CTRL ; 
 int /*<<< orphan*/  REG_TX_FIFO_CTRL ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct zx_tdm_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned int zx_tdm_readl (struct zx_tdm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_tdm_rx_dma_en (struct zx_tdm_info*,int) ; 
 int /*<<< orphan*/  zx_tdm_rx_en (struct zx_tdm_info*,int) ; 
 int /*<<< orphan*/  zx_tdm_tx_dma_en (struct zx_tdm_info*,int) ; 
 int /*<<< orphan*/  zx_tdm_tx_en (struct zx_tdm_info*,int) ; 
 int /*<<< orphan*/  zx_tdm_writel (struct zx_tdm_info*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int zx_tdm_trigger(struct snd_pcm_substream *substream, int cmd,
			  struct snd_soc_dai *dai)
{
	int capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	struct zx_tdm_info *zx_tdm = dev_get_drvdata(dai->dev);
	unsigned int val;
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (capture) {
			val = zx_tdm_readl(zx_tdm, REG_RX_FIFO_CTRL);
			val |= FIFOCTRL_RX_FIFO_RST;
			zx_tdm_writel(zx_tdm, REG_RX_FIFO_CTRL, val);

			zx_tdm_rx_dma_en(zx_tdm, true);
		} else {
			val = zx_tdm_readl(zx_tdm, REG_TX_FIFO_CTRL);
			val |= FIFOCTRL_TX_FIFO_RST;
			zx_tdm_writel(zx_tdm, REG_TX_FIFO_CTRL, val);

			zx_tdm_tx_dma_en(zx_tdm, true);
		}
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (capture)
			zx_tdm_rx_en(zx_tdm, true);
		else
			zx_tdm_tx_en(zx_tdm, true);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (capture)
			zx_tdm_rx_dma_en(zx_tdm, false);
		else
			zx_tdm_tx_dma_en(zx_tdm, false);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (capture)
			zx_tdm_rx_en(zx_tdm, false);
		else
			zx_tdm_tx_en(zx_tdm, false);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}