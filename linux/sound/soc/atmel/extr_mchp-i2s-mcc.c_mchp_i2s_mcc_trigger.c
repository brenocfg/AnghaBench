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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct mchp_i2s_mcc_dev {int gclk_running; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  gclk; scalar_t__ gclk_use; int /*<<< orphan*/  channels; int /*<<< orphan*/  rx_rdy; int /*<<< orphan*/  tx_rdy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MCHP_I2SMCC_CR ; 
 int MCHP_I2SMCC_CR_CKEN ; 
 int MCHP_I2SMCC_CR_RXDIS ; 
 int MCHP_I2SMCC_CR_RXEN ; 
 int MCHP_I2SMCC_CR_TXDIS ; 
 int MCHP_I2SMCC_CR_TXEN ; 
 int /*<<< orphan*/  MCHP_I2SMCC_IERA ; 
 int MCHP_I2SMCC_INT_RXRDY_MASK (int /*<<< orphan*/ ) ; 
 int MCHP_I2SMCC_INT_TXRDY_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCHP_I2SMCC_SR ; 
 int MCHP_I2SMCC_SR_RXEN ; 
 int MCHP_I2SMCC_SR_TXEN ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mchp_i2s_mcc_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mchp_i2s_mcc_trigger(struct snd_pcm_substream *substream, int cmd,
				struct snd_soc_dai *dai)
{
	struct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 cr = 0;
	u32 iera = 0;
	u32 sr;
	int err;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (is_playback)
			cr = MCHP_I2SMCC_CR_TXEN | MCHP_I2SMCC_CR_CKEN;
		else
			cr = MCHP_I2SMCC_CR_RXEN | MCHP_I2SMCC_CR_CKEN;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		regmap_read(dev->regmap, MCHP_I2SMCC_SR, &sr);
		if (is_playback && (sr & MCHP_I2SMCC_SR_TXEN)) {
			cr = MCHP_I2SMCC_CR_TXDIS;
			dev->tx_rdy = 0;
			/*
			 * Enable Tx Ready interrupts on all channels
			 * to assure all data is sent
			 */
			iera = MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels);
		} else if (!is_playback && (sr & MCHP_I2SMCC_SR_RXEN)) {
			cr = MCHP_I2SMCC_CR_RXDIS;
			dev->rx_rdy = 0;
			/*
			 * Enable Rx Ready interrupts on all channels
			 * to assure all data is received
			 */
			iera = MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels);
		}
		break;
	default:
		return -EINVAL;
	}

	if ((cr & MCHP_I2SMCC_CR_CKEN) && dev->gclk_use &&
	    !dev->gclk_running) {
		err = clk_enable(dev->gclk);
		if (err) {
			dev_err_once(dev->dev, "failed to enable GCLK: %d\n",
				     err);
		} else {
			dev->gclk_running = 1;
		}
	}

	regmap_write(dev->regmap, MCHP_I2SMCC_IERA, iera);
	regmap_write(dev->regmap, MCHP_I2SMCC_CR, cr);

	return 0;
}