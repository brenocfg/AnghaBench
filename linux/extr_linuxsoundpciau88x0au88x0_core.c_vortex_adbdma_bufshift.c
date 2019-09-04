#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* card; int /*<<< orphan*/  mmio; TYPE_3__* dma_adb; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_7__ {int nr_periods; int period_real; int period_virt; int period_bytes; int /*<<< orphan*/  substream; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADB_SUBBUF_MASK ; 
 int ADB_SUBBUF_SHIFT ; 
 scalar_t__ VORTEX_ADBDMA_BUFBASE ; 
 scalar_t__ VORTEX_ADBDMA_STAT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_sgbuf_get_addr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vortex_adbdma_bufshift(vortex_t * vortex, int adbdma)
{
	stream_t *dma = &vortex->dma_adb[adbdma];
	int page, p, pp, delta, i;

	page =
	    (hwread(vortex->mmio, VORTEX_ADBDMA_STAT + (adbdma << 2)) &
	     ADB_SUBBUF_MASK) >> ADB_SUBBUF_SHIFT;
	if (dma->nr_periods >= 4)
		delta = (page - dma->period_real) & 3;
	else {
		delta = (page - dma->period_real);
		if (delta < 0)
			delta += dma->nr_periods;
	}
	if (delta == 0)
		return 0;

	/* refresh hw page table */
	if (dma->nr_periods > 4) {
		for (i = 0; i < delta; i++) {
			/* p: audio buffer page index */
			p = dma->period_virt + i + 4;
			if (p >= dma->nr_periods)
				p -= dma->nr_periods;
			/* pp: hardware DMA page index. */
			pp = dma->period_real + i;
			if (pp >= 4)
				pp -= 4;
			//hwwrite(vortex->mmio, VORTEX_ADBDMA_BUFBASE+(((adbdma << 2)+pp) << 2), dma->table[p].addr);
			hwwrite(vortex->mmio,
				VORTEX_ADBDMA_BUFBASE + (((adbdma << 2) + pp) << 2),
				snd_pcm_sgbuf_get_addr(dma->substream,
				dma->period_bytes * p));
			/* Force write thru cache. */
			hwread(vortex->mmio, VORTEX_ADBDMA_BUFBASE +
			       (((adbdma << 2) + pp) << 2));
		}
	}
	dma->period_virt += delta;
	dma->period_real = page;
	if (dma->period_virt >= dma->nr_periods)
		dma->period_virt -= dma->nr_periods;
	if (delta != 1)
		dev_info(vortex->card->dev,
			 "%d virt=%d, real=%d, delta=%d\n",
			 adbdma, dma->period_virt, dma->period_real, delta);

	return delta;
}