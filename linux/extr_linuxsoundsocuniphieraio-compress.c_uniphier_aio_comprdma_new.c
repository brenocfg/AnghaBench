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
struct uniphier_aio_sub {size_t compr_bytes; int /*<<< orphan*/ * compr_area; int /*<<< orphan*/  compr_addr; TYPE_2__* swm; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; struct snd_compr* compr; } ;
struct snd_compr {size_t direction; TYPE_1__* card; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ dir; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 size_t AUD_RING_SIZE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aio_comprdma_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_compr *compr = rtd->compr;
	struct device *dev = compr->card->dev;
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[compr->direction];
	size_t size = AUD_RING_SIZE;
	int dma_dir = DMA_FROM_DEVICE, ret;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(33));
	if (ret)
		return ret;

	sub->compr_area = kzalloc(size, GFP_KERNEL);
	if (!sub->compr_area)
		return -ENOMEM;

	if (sub->swm->dir == PORT_DIR_OUTPUT)
		dma_dir = DMA_TO_DEVICE;

	sub->compr_addr = dma_map_single(dev, sub->compr_area, size, dma_dir);
	if (dma_mapping_error(dev, sub->compr_addr)) {
		kfree(sub->compr_area);
		sub->compr_area = NULL;

		return -ENOMEM;
	}

	sub->compr_bytes = size;

	return 0;
}