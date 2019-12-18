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
struct img_spdif_out {int /*<<< orphan*/  dma_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spdif_out_controls ; 
 int /*<<< orphan*/  snd_soc_add_dai_controls (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct img_spdif_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_spdif_out_dai_probe(struct snd_soc_dai *dai)
{
	struct img_spdif_out *spdif = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdif->dma_data, NULL);

	snd_soc_add_dai_controls(dai, img_spdif_out_controls,
			ARRAY_SIZE(img_spdif_out_controls));

	return 0;
}