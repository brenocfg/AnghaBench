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
struct fsl_asrc {int /*<<< orphan*/  dma_params_rx; int /*<<< orphan*/  dma_params_tx; } ;

/* Variables and functions */
 struct fsl_asrc* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_asrc_dai_probe(struct snd_soc_dai *dai)
{
	struct fsl_asrc *asrc_priv = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &asrc_priv->dma_params_tx,
				  &asrc_priv->dma_params_rx);

	return 0;
}