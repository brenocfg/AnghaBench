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
struct fsl_spdif_priv {int /*<<< orphan*/  dma_params_rx; int /*<<< orphan*/  dma_params_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_spdif_ctrls ; 
 int /*<<< orphan*/  snd_soc_add_dai_controls (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_spdif_dai_probe(struct snd_soc_dai *dai)
{
	struct fsl_spdif_priv *spdif_private = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdif_private->dma_params_tx,
				  &spdif_private->dma_params_rx);

	snd_soc_add_dai_controls(dai, fsl_spdif_ctrls, ARRAY_SIZE(fsl_spdif_ctrls));

	return 0;
}