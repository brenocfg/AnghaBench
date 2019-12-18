#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * filter_data; } ;
struct spdif_in_dev {TYPE_1__ dma_params_rx; int /*<<< orphan*/  dma_params; } ;
struct snd_soc_dai {TYPE_1__* capture_dma_data; } ;

/* Variables and functions */
 struct spdif_in_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int spdif_in_dai_probe(struct snd_soc_dai *dai)
{
	struct spdif_in_dev *host = snd_soc_dai_get_drvdata(dai);

	host->dma_params_rx.filter_data = &host->dma_params;
	dai->capture_dma_data = &host->dma_params_rx;

	return 0;
}