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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct mchp_i2s_mcc_dev {int tx_rdy; int rx_rdy; scalar_t__ gclk_use; int /*<<< orphan*/  gclk; scalar_t__ gclk_running; int /*<<< orphan*/  regmap; int /*<<< orphan*/  channels; int /*<<< orphan*/  dev; int /*<<< orphan*/  wq_rxrdy; int /*<<< orphan*/  wq_txrdy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHP_I2SMCC_CR ; 
 int /*<<< orphan*/  MCHP_I2SMCC_CR_CKDIS ; 
 int /*<<< orphan*/  MCHP_I2SMCC_IDRA ; 
 int /*<<< orphan*/  MCHP_I2SMCC_INT_RXRDY_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCHP_I2SMCC_INT_TXRDY_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mchp_i2s_mcc_is_running (struct mchp_i2s_mcc_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mchp_i2s_mcc_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mchp_i2s_mcc_hw_free(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	long err;

	if (is_playback) {
		err = wait_event_interruptible_timeout(dev->wq_txrdy,
						       dev->tx_rdy,
						       msecs_to_jiffies(500));
		if (err == 0) {
			dev_warn_once(dev->dev,
				      "Timeout waiting for Tx ready\n");
			regmap_write(dev->regmap, MCHP_I2SMCC_IDRA,
				     MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels));
			dev->tx_rdy = 1;
		}
	} else {
		err = wait_event_interruptible_timeout(dev->wq_rxrdy,
						       dev->rx_rdy,
						       msecs_to_jiffies(500));
		if (err == 0) {
			dev_warn_once(dev->dev,
				      "Timeout waiting for Rx ready\n");
			regmap_write(dev->regmap, MCHP_I2SMCC_IDRA,
				     MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels));
			dev->rx_rdy = 1;
		}
	}

	if (!mchp_i2s_mcc_is_running(dev)) {
		regmap_write(dev->regmap, MCHP_I2SMCC_CR, MCHP_I2SMCC_CR_CKDIS);

		if (dev->gclk_running) {
			clk_disable(dev->gclk);
			dev->gclk_running = 0;
		}
		if (dev->gclk_use) {
			clk_unprepare(dev->gclk);
			dev->gclk_use = 0;
		}
	}

	return 0;
}