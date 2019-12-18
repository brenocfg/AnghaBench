#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ux500_msp_i2s_drvdata {TYPE_1__* msp; int /*<<< orphan*/  slot_width; } ;
struct snd_soc_dai {TYPE_4__* dev; } ;
struct msp_i2s_platform_data {int dummy; } ;
struct TYPE_8__ {struct msp_i2s_platform_data* platform_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_size; } ;
struct TYPE_5__ {TYPE_3__ capture_dma_data; TYPE_2__ playback_dma_data; } ;

/* Variables and functions */
 struct ux500_msp_i2s_drvdata* dev_get_drvdata (TYPE_4__*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,TYPE_2__*,TYPE_3__*) ; 
 int ux500_msp_dai_of_probe (struct snd_soc_dai*) ; 

__attribute__((used)) static int ux500_msp_dai_probe(struct snd_soc_dai *dai)
{
	struct ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(dai->dev);
	struct msp_i2s_platform_data *pdata = dai->dev->platform_data;
	int ret;

	if (!pdata) {
		ret = ux500_msp_dai_of_probe(dai);
		return ret;
	}

	drvdata->msp->playback_dma_data.data_size = drvdata->slot_width;
	drvdata->msp->capture_dma_data.data_size = drvdata->slot_width;

	snd_soc_dai_init_dma_data(dai,
				  &drvdata->msp->playback_dma_data,
				  &drvdata->msp->capture_dma_data);
	return 0;
}