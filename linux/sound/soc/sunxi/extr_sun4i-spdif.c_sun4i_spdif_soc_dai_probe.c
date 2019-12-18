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
struct sun4i_spdif_dev {int /*<<< orphan*/  dma_params_tx; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 struct sun4i_spdif_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4i_spdif_soc_dai_probe(struct snd_soc_dai *dai)
{
	struct sun4i_spdif_dev *host = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &host->dma_params_tx, NULL);
	return 0;
}