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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct ep93xx_ac97_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97RXCR (int) ; 
 unsigned int AC97RXCR_CM ; 
 unsigned int AC97RXCR_REN ; 
 unsigned int AC97RXCR_RX3 ; 
 unsigned int AC97RXCR_RX4 ; 
 int /*<<< orphan*/  AC97SR (int) ; 
 unsigned int AC97SR_TXFE ; 
 unsigned int AC97SR_TXUE ; 
 int /*<<< orphan*/  AC97TXCR (int) ; 
 unsigned int AC97TXCR_CM ; 
 unsigned int AC97TXCR_TEN ; 
 unsigned int AC97TXCR_TX3 ; 
 unsigned int AC97TXCR_TX4 ; 
 unsigned long AC97_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int ep93xx_ac97_read_reg (struct ep93xx_ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_ac97_write_reg (struct ep93xx_ac97_info*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long jiffies ; 
 struct ep93xx_ac97_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int ep93xx_ac97_trigger(struct snd_pcm_substream *substream,
			       int cmd, struct snd_soc_dai *dai)
{
	struct ep93xx_ac97_info *info = snd_soc_dai_get_drvdata(dai);
	unsigned v = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			/*
			 * Enable compact mode, TX slots 3 & 4, and the TX FIFO
			 * itself.
			 */
			v |= AC97TXCR_CM;
			v |= AC97TXCR_TX3 | AC97TXCR_TX4;
			v |= AC97TXCR_TEN;
			ep93xx_ac97_write_reg(info, AC97TXCR(1), v);
		} else {
			/*
			 * Enable compact mode, RX slots 3 & 4, and the RX FIFO
			 * itself.
			 */
			v |= AC97RXCR_CM;
			v |= AC97RXCR_RX3 | AC97RXCR_RX4;
			v |= AC97RXCR_REN;
			ep93xx_ac97_write_reg(info, AC97RXCR(1), v);
		}
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			/*
			 * As per Cirrus EP93xx errata described below:
			 *
			 * http://www.cirrus.com/en/pubs/errata/ER667E2B.pdf
			 *
			 * we will wait for the TX FIFO to be empty before
			 * clearing the TEN bit.
			 */
			unsigned long timeout = jiffies + AC97_TIMEOUT;

			do {
				v = ep93xx_ac97_read_reg(info, AC97SR(1));
				if (time_after(jiffies, timeout)) {
					dev_warn(info->dev, "TX timeout\n");
					break;
				}
			} while (!(v & (AC97SR_TXFE | AC97SR_TXUE)));

			/* disable the TX FIFO */
			ep93xx_ac97_write_reg(info, AC97TXCR(1), 0);
		} else {
			/* disable the RX FIFO */
			ep93xx_ac97_write_reg(info, AC97RXCR(1), 0);
		}
		break;

	default:
		dev_warn(info->dev, "unknown command %d\n", cmd);
		return -EINVAL;
	}

	return 0;
}