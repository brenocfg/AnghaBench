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
typedef  int /*<<< orphan*/  uint32_t ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct bcm2835_i2s_dev {int /*<<< orphan*/  i2s_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_I2S_CS_A_REG ; 
 int /*<<< orphan*/  BCM2835_I2S_RXON ; 
 int /*<<< orphan*/  BCM2835_I2S_TXON ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  bcm2835_i2s_start_clock (struct bcm2835_i2s_dev*) ; 
 int /*<<< orphan*/  bcm2835_i2s_stop (struct bcm2835_i2s_dev*,struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm2835_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int bcm2835_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			       struct snd_soc_dai *dai)
{
	struct bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	uint32_t mask;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		bcm2835_i2s_start_clock(dev);

		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			mask = BCM2835_I2S_RXON;
		else
			mask = BCM2835_I2S_TXON;

		regmap_update_bits(dev->i2s_regmap,
				BCM2835_I2S_CS_A_REG, mask, mask);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		bcm2835_i2s_stop(dev, substream, dai);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}