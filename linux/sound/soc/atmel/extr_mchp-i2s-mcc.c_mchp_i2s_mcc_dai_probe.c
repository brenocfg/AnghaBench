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
struct mchp_i2s_mcc_dev {int tx_rdy; int rx_rdy; int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; int /*<<< orphan*/  wq_rxrdy; int /*<<< orphan*/  wq_txrdy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct mchp_i2s_mcc_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mchp_i2s_mcc_dai_probe(struct snd_soc_dai *dai)
{
	struct mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	init_waitqueue_head(&dev->wq_txrdy);
	init_waitqueue_head(&dev->wq_rxrdy);
	dev->tx_rdy = 1;
	dev->rx_rdy = 1;

	snd_soc_dai_init_dma_data(dai, &dev->playback, &dev->capture);

	return 0;
}