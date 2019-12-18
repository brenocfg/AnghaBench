#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_wt; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_7__ {int period_bytes; int nr_periods; int cfg0; int cfg1; int /*<<< orphan*/  substream; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  VORTEX_WTDMA_BUFBASE ; 
 scalar_t__ VORTEX_WTDMA_BUFCFG0 ; 
 scalar_t__ VORTEX_WTDMA_BUFCFG1 ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int snd_pcm_sgbuf_get_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vortex_wtdma_setfirstbuffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_setstartbuffer (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_wtdma_setbuffers(vortex_t * vortex, int wtdma,
			int psize, int count)
{
	stream_t *dma = &vortex->dma_wt[wtdma];

	dma->period_bytes = psize;
	dma->nr_periods = count;

	dma->cfg0 = 0;
	dma->cfg1 = 0;
	switch (count) {
		/* Four or more pages */
	default:
	case 4:
		dma->cfg1 |= 0x88000000 | 0x44000000 | 0x30000000 | (psize-1);
		hwwrite(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4) + 0xc,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 3));
		/* fall through */
		/* 3 pages */
	case 3:
		dma->cfg0 |= 0x12000000;
		dma->cfg1 |= 0x80000000 | 0x40000000 | ((psize-1) << 0xc);
		hwwrite(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4)  + 0x8,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 2));
		/* fall through */
		/* 2 pages */
	case 2:
		dma->cfg0 |= 0x88000000 | 0x44000000 | 0x10000000 | (psize-1);
		hwwrite(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4) + 0x4,
			snd_pcm_sgbuf_get_addr(dma->substream, psize));
		/* fall through */
		/* 1 page */
	case 1:
		dma->cfg0 |= 0x80000000 | 0x40000000 | ((psize-1) << 0xc);
		hwwrite(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4),
			snd_pcm_sgbuf_get_addr(dma->substream, 0));
		break;
	}
	hwwrite(vortex->mmio, VORTEX_WTDMA_BUFCFG0 + (wtdma << 3), dma->cfg0);
	hwwrite(vortex->mmio, VORTEX_WTDMA_BUFCFG1 + (wtdma << 3), dma->cfg1);

	vortex_wtdma_setfirstbuffer(vortex, wtdma);
	vortex_wtdma_setstartbuffer(vortex, wtdma, 0);
}