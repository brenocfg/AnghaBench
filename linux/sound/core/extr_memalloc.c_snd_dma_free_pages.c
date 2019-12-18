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
struct TYPE_2__ {int type; } ;
struct snd_dma_buffer {TYPE_1__ dev; int /*<<< orphan*/  bytes; int /*<<< orphan*/  area; } ;

/* Variables and functions */
#define  SNDRV_DMA_TYPE_CONTINUOUS 133 
#define  SNDRV_DMA_TYPE_DEV 132 
#define  SNDRV_DMA_TYPE_DEV_IRAM 131 
#define  SNDRV_DMA_TYPE_DEV_SG 130 
#define  SNDRV_DMA_TYPE_DEV_UC 129 
#define  SNDRV_DMA_TYPE_DEV_UC_SG 128 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snd_free_dev_iram (struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_free_dev_pages (struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_free_sgbuf_pages (struct snd_dma_buffer*) ; 

void snd_dma_free_pages(struct snd_dma_buffer *dmab)
{
	switch (dmab->dev.type) {
	case SNDRV_DMA_TYPE_CONTINUOUS:
		free_pages_exact(dmab->area, dmab->bytes);
		break;
#ifdef CONFIG_HAS_DMA
#ifdef CONFIG_GENERIC_ALLOCATOR
	case SNDRV_DMA_TYPE_DEV_IRAM:
		snd_free_dev_iram(dmab);
		break;
#endif /* CONFIG_GENERIC_ALLOCATOR */
	case SNDRV_DMA_TYPE_DEV:
	case SNDRV_DMA_TYPE_DEV_UC:
		snd_free_dev_pages(dmab);
		break;
#endif
#ifdef CONFIG_SND_DMA_SGBUF
	case SNDRV_DMA_TYPE_DEV_SG:
	case SNDRV_DMA_TYPE_DEV_UC_SG:
		snd_free_sgbuf_pages(dmab);
		break;
#endif
	default:
		pr_err("snd-malloc: invalid device type %d\n", dmab->dev.type);
	}
}