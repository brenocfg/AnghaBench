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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  pcm; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct device {int dummy; } ;
struct audio_drv_data {int asic_type; } ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
#define  CHIP_STONEY 128 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  MAX_BUFFER ; 
 int /*<<< orphan*/  MIN_BUFFER ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  ST_MAX_BUFFER ; 
 int /*<<< orphan*/  ST_MIN_BUFFER ; 
 struct audio_drv_data* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acp_dma_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd,
								    DRV_NAME);
	struct audio_drv_data *adata = dev_get_drvdata(component->dev);
	struct device *parent = component->dev->parent;

	switch (adata->asic_type) {
	case CHIP_STONEY:
		snd_pcm_lib_preallocate_pages_for_all(rtd->pcm,
						      SNDRV_DMA_TYPE_DEV,
						      parent,
						      ST_MIN_BUFFER,
						      ST_MAX_BUFFER);
		break;
	default:
		snd_pcm_lib_preallocate_pages_for_all(rtd->pcm,
						      SNDRV_DMA_TYPE_DEV,
						      parent,
						      MIN_BUFFER,
						      MAX_BUFFER);
		break;
	}
	return 0;
}