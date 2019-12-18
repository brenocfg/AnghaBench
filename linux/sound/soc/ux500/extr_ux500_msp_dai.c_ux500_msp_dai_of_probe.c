#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ux500_msp_i2s_drvdata {TYPE_3__* msp; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_dmaengine_dai_dma_data {int maxburst; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_rx_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_rx_addr; } ;
struct TYPE_6__ {TYPE_2__ capture_dma_data; TYPE_1__ playback_dma_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ux500_msp_i2s_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct snd_dmaengine_dai_dma_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,struct snd_dmaengine_dai_dma_data*,struct snd_dmaengine_dai_dma_data*) ; 

__attribute__((used)) static int ux500_msp_dai_of_probe(struct snd_soc_dai *dai)
{
	struct ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	struct snd_dmaengine_dai_dma_data *playback_dma_data;
	struct snd_dmaengine_dai_dma_data *capture_dma_data;

	playback_dma_data = devm_kzalloc(dai->dev,
					 sizeof(*playback_dma_data),
					 GFP_KERNEL);
	if (!playback_dma_data)
		return -ENOMEM;

	capture_dma_data = devm_kzalloc(dai->dev,
					sizeof(*capture_dma_data),
					GFP_KERNEL);
	if (!capture_dma_data)
		return -ENOMEM;

	playback_dma_data->addr = drvdata->msp->playback_dma_data.tx_rx_addr;
	capture_dma_data->addr = drvdata->msp->capture_dma_data.tx_rx_addr;

	playback_dma_data->maxburst = 4;
	capture_dma_data->maxburst = 4;

	snd_soc_dai_init_dma_data(dai, playback_dma_data, capture_dma_data);

	return 0;
}