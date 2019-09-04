#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_adb; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_5__ {int nr_periods; int period_virt; int period_real; int period_bytes; int /*<<< orphan*/  substream; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 scalar_t__ VORTEX_ADBDMA_BUFBASE ; 
 int /*<<< orphan*/  hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_sgbuf_get_addr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vortex_adbdma_resetup(vortex_t *vortex, int adbdma) {
	stream_t *dma = &vortex->dma_adb[adbdma];
	int p, pp, i;

	/* refresh hw page table */
	for (i=0 ; i < 4 && i < dma->nr_periods; i++) {
		/* p: audio buffer page index */
		p = dma->period_virt + i;
		if (p >= dma->nr_periods)
			p -= dma->nr_periods;
		/* pp: hardware DMA page index. */
		pp = dma->period_real + i;
		if (dma->nr_periods < 4) {
			if (pp >= dma->nr_periods)
				pp -= dma->nr_periods;
		}
		else {
			if (pp >= 4)
				pp -= 4;
		}
		hwwrite(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (((adbdma << 2) + pp) << 2),
			snd_pcm_sgbuf_get_addr(dma->substream,
					       dma->period_bytes * p));
		/* Force write thru cache. */
		hwread(vortex->mmio, VORTEX_ADBDMA_BUFBASE + (((adbdma << 2)+pp) << 2));
	}
}