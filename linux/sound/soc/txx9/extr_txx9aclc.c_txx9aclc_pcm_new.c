#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct txx9aclc_soc_device {TYPE_2__* dmadata; } ;
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; struct snd_soc_dai* cpu_dai; TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm {int dummy; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dma_chan; struct resource* dma_res; int /*<<< orphan*/  stream; } ;
struct TYPE_3__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct txx9aclc_soc_device* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int txx9aclc_dma_init (struct txx9aclc_soc_device*,TYPE_2__*) ; 

__attribute__((used)) static int txx9aclc_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_soc_dai *dai = rtd->cpu_dai;
	struct snd_pcm *pcm = rtd->pcm;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct platform_device *pdev = to_platform_device(component->dev);
	struct txx9aclc_soc_device *dev;
	struct resource *r;
	int i;
	int ret;

	/* at this point onwards the AC97 component has probed and this will be valid */
	dev = snd_soc_dai_get_drvdata(dai);

	dev->dmadata[0].stream = SNDRV_PCM_STREAM_PLAYBACK;
	dev->dmadata[1].stream = SNDRV_PCM_STREAM_CAPTURE;
	for (i = 0; i < 2; i++) {
		r = platform_get_resource(pdev, IORESOURCE_DMA, i);
		if (!r) {
			ret = -EBUSY;
			goto exit;
		}
		dev->dmadata[i].dma_res = r;
		ret = txx9aclc_dma_init(dev, &dev->dmadata[i]);
		if (ret)
			goto exit;
	}

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
		card->dev, 64 * 1024, 4 * 1024 * 1024);
	return 0;

exit:
	for (i = 0; i < 2; i++) {
		if (dev->dmadata[i].dma_chan)
			dma_release_channel(dev->dmadata[i].dma_chan);
		dev->dmadata[i].dma_chan = NULL;
	}
	return ret;
}