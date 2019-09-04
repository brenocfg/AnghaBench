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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct dma_slave_config {int dst_maxburst; int src_maxburst; int device_fc; scalar_t__ dst_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  dst_addr_width; } ;
struct atmel_classd {scalar_t__ phy_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CLASSD_THR ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_physical_width (struct snd_pcm_hw_params*) ; 
 struct atmel_classd* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atmel_classd_platform_configure_dma(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct dma_slave_config *slave_config)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct atmel_classd *dd = snd_soc_card_get_drvdata(rtd->card);

	if (params_physical_width(params) != 16) {
		dev_err(dd->dev,
			"only supports 16-bit audio data\n");
		return -EINVAL;
	}

	if (params_channels(params) == 1)
		slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	else
		slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	slave_config->direction		= DMA_MEM_TO_DEV;
	slave_config->dst_addr		= dd->phy_base + CLASSD_THR;
	slave_config->dst_maxburst	= 1;
	slave_config->src_maxburst	= 1;
	slave_config->device_fc		= false;

	return 0;
}