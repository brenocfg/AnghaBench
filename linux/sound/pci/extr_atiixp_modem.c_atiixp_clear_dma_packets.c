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
struct snd_pcm_substream {int dummy; } ;
struct atiixp_modem {scalar_t__ remap_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * area; } ;
struct atiixp_dma {TYPE_2__ desc_buf; TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ llp_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void atiixp_clear_dma_packets(struct atiixp_modem *chip,
				     struct atiixp_dma *dma,
				     struct snd_pcm_substream *substream)
{
	if (dma->desc_buf.area) {
		writel(0, chip->remap_addr + dma->ops->llp_offset);
		snd_dma_free_pages(&dma->desc_buf);
		dma->desc_buf.area = NULL;
	}
}