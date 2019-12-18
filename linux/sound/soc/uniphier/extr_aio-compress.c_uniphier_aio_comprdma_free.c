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
struct uniphier_aio_sub {int /*<<< orphan*/ * compr_area; int /*<<< orphan*/  compr_bytes; int /*<<< orphan*/  compr_addr; TYPE_1__* swm; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; struct snd_compr* compr; } ;
struct snd_compr {size_t direction; TYPE_2__* card; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;
struct TYPE_3__ {scalar_t__ dir; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aio_comprdma_free(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_compr *compr = rtd->compr;
	struct device *dev = compr->card->dev;
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[compr->direction];
	int dma_dir = DMA_FROM_DEVICE;

	if (sub->swm->dir == PORT_DIR_OUTPUT)
		dma_dir = DMA_TO_DEVICE;

	dma_unmap_single(dev, sub->compr_addr, sub->compr_bytes, dma_dir);
	kfree(sub->compr_area);
	sub->compr_area = NULL;

	return 0;
}