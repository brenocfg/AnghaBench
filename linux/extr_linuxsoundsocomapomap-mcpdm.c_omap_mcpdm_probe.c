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
struct snd_soc_dai {int dummy; } ;
struct omap_mcpdm {int /*<<< orphan*/ * dma_data; TYPE_1__* config; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCPDM_REG_CTRL ; 
 int MCPDM_UP_THRES_MAX ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_mcpdm_irq_handler ; 
 int /*<<< orphan*/  omap_mcpdm_write (struct omap_mcpdm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 struct omap_mcpdm* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_mcpdm_probe(struct snd_soc_dai *dai)
{
	struct omap_mcpdm *mcpdm = snd_soc_dai_get_drvdata(dai);
	int ret;

	pm_runtime_enable(mcpdm->dev);

	/* Disable lines while request is ongoing */
	pm_runtime_get_sync(mcpdm->dev);
	omap_mcpdm_write(mcpdm, MCPDM_REG_CTRL, 0x00);

	ret = request_irq(mcpdm->irq, omap_mcpdm_irq_handler, 0, "McPDM",
			  (void *)mcpdm);

	pm_runtime_put_sync(mcpdm->dev);

	if (ret) {
		dev_err(mcpdm->dev, "Request for IRQ failed\n");
		pm_runtime_disable(mcpdm->dev);
	}

	/* Configure McPDM threshold values */
	mcpdm->config[SNDRV_PCM_STREAM_PLAYBACK].threshold = 2;
	mcpdm->config[SNDRV_PCM_STREAM_CAPTURE].threshold =
							MCPDM_UP_THRES_MAX - 3;

	snd_soc_dai_init_dma_data(dai,
				  &mcpdm->dma_data[SNDRV_PCM_STREAM_PLAYBACK],
				  &mcpdm->dma_data[SNDRV_PCM_STREAM_CAPTURE]);

	return ret;
}