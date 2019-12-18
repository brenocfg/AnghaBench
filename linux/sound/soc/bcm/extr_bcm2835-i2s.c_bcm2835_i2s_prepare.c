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
typedef  int uint32_t ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct bcm2835_i2s_dev {int /*<<< orphan*/  i2s_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_I2S_CS_A_REG ; 
 int BCM2835_I2S_RXD ; 
 int BCM2835_I2S_TXE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bcm2835_i2s_clear_fifos (struct bcm2835_i2s_dev*,int,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct bcm2835_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int bcm2835_i2s_prepare(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	uint32_t cs_reg;

	/*
	 * Clear both FIFOs if the one that should be started
	 * is not empty at the moment. This should only happen
	 * after overrun. Otherwise, hw_params would have cleared
	 * the FIFO.
	 */
	regmap_read(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &cs_reg);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			&& !(cs_reg & BCM2835_I2S_TXE))
		bcm2835_i2s_clear_fifos(dev, true, false);
	else if (substream->stream == SNDRV_PCM_STREAM_CAPTURE
			&& (cs_reg & BCM2835_I2S_RXD))
		bcm2835_i2s_clear_fifos(dev, false, true);

	return 0;
}