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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  id; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {size_t stream; struct snd_soc_pcm_runtime* private_data; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct mmp_dma_data {int /*<<< orphan*/  ssp_id; struct resource* dma_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  filter ; 
 int /*<<< orphan*/ * mmp_pcm_hardware ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,size_t) ; 
 int snd_dmaengine_pcm_open_request_chan (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct mmp_dma_data*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmp_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct platform_device *pdev = to_platform_device(component->dev);
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct mmp_dma_data dma_data;
	struct resource *r;

	r = platform_get_resource(pdev, IORESOURCE_DMA, substream->stream);
	if (!r)
		return -EBUSY;

	snd_soc_set_runtime_hwparams(substream,
				&mmp_pcm_hardware[substream->stream]);

	dma_data.dma_res = r;
	dma_data.ssp_id = cpu_dai->id;

	return snd_dmaengine_pcm_open_request_chan(substream, filter,
		    &dma_data);
}