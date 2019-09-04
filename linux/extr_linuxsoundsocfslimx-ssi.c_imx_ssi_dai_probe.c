#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct snd_soc_dai {TYPE_2__* capture_dma_data; TYPE_1__* playback_dma_data; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  maxburst; } ;
struct TYPE_3__ {int /*<<< orphan*/  maxburst; } ;
struct imx_ssi {TYPE_2__ dma_params_rx; TYPE_1__ dma_params_tx; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SSI_SFCSR ; 
 int SSI_SFCSR_RFWM0 (int /*<<< orphan*/ ) ; 
 int SSI_SFCSR_TFWM0 (int /*<<< orphan*/ ) ; 
 struct imx_ssi* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct imx_ssi*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imx_ssi_dai_probe(struct snd_soc_dai *dai)
{
	struct imx_ssi *ssi = dev_get_drvdata(dai->dev);
	uint32_t val;

	snd_soc_dai_set_drvdata(dai, ssi);

	val = SSI_SFCSR_TFWM0(ssi->dma_params_tx.maxburst) |
		SSI_SFCSR_RFWM0(ssi->dma_params_rx.maxburst);
	writel(val, ssi->base + SSI_SFCSR);

	/* Tx/Rx config */
	dai->playback_dma_data = &ssi->dma_params_tx;
	dai->capture_dma_data = &ssi->dma_params_rx;

	return 0;
}