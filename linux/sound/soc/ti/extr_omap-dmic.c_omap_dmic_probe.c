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
struct omap_dmic {int /*<<< orphan*/  dma_data; scalar_t__ threshold; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DMIC_CTRL_REG ; 
 scalar_t__ OMAP_DMIC_THRES_MAX ; 
 int /*<<< orphan*/  omap_dmic_write (struct omap_dmic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct omap_dmic* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_dmic_probe(struct snd_soc_dai *dai)
{
	struct omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	pm_runtime_enable(dmic->dev);

	/* Disable lines while request is ongoing */
	pm_runtime_get_sync(dmic->dev);
	omap_dmic_write(dmic, OMAP_DMIC_CTRL_REG, 0x00);
	pm_runtime_put_sync(dmic->dev);

	/* Configure DMIC threshold value */
	dmic->threshold = OMAP_DMIC_THRES_MAX - 3;

	snd_soc_dai_init_dma_data(dai, NULL, &dmic->dma_data);

	return 0;
}