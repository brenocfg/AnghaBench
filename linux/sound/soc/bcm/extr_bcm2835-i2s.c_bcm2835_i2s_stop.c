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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct bcm2835_i2s_dev {int fmt; int /*<<< orphan*/  i2s_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_I2S_CS_A_REG ; 
 int /*<<< orphan*/  BCM2835_I2S_RXON ; 
 int /*<<< orphan*/  BCM2835_I2S_TXON ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int SND_SOC_DAIFMT_CONT ; 
 int /*<<< orphan*/  bcm2835_i2s_stop_clock (struct bcm2835_i2s_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_i2s_stop(struct bcm2835_i2s_dev *dev,
		struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	uint32_t mask;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mask = BCM2835_I2S_RXON;
	else
		mask = BCM2835_I2S_TXON;

	regmap_update_bits(dev->i2s_regmap,
			BCM2835_I2S_CS_A_REG, mask, 0);

	/* Stop also the clock when not SND_SOC_DAIFMT_CONT */
	if (!dai->active && !(dev->fmt & SND_SOC_DAIFMT_CONT))
		bcm2835_i2s_stop_clock(dev);
}