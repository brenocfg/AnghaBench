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
struct TYPE_6__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_adb; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_7__ {int period_bytes; int nr_periods; int cfg0; int cfg1; int /*<<< orphan*/  substream; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  VORTEX_ADBDMA_BUFBASE ; 
 scalar_t__ VORTEX_ADBDMA_BUFCFG0 ; 
 scalar_t__ VORTEX_ADBDMA_BUFCFG1 ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int snd_pcm_sgbuf_get_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vortex_adbdma_setfirstbuffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vortex_adbdma_setstartbuffer (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_adbdma_setbuffers(vortex_t * vortex, int adbdma,
			 int psize, int count)
{
	stream_t *dma = &vortex->dma_adb[adbdma];

	dma->period_bytes = psize;
	dma->nr_periods = count;

	dma->cfg0 = 0;
	dma->cfg1 = 0;
	switch (count) {
		/* Four or more pages */
	default:
	case 4:
		dma->cfg1 |= 0x88000000 | 0x44000000 | 0x30000000 | (psize - 1);
		hwwrite(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0xc,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 3));
		/* fall through */
		/* 3 pages */
	case 3:
		dma->cfg0 |= 0x12000000;
		dma->cfg1 |= 0x80000000 | 0x40000000 | ((psize - 1) << 0xc);
		hwwrite(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0x8,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 2));
		/* fall through */
		/* 2 pages */
	case 2:
		dma->cfg0 |= 0x88000000 | 0x44000000 | 0x10000000 | (psize - 1);
		hwwrite(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0x4,
			snd_pcm_sgbuf_get_addr(dma->substream, psize));
		/* fall through */
		/* 1 page */
	case 1:
		dma->cfg0 |= 0x80000000 | 0x40000000 | ((psize - 1) << 0xc);
		hwwrite(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4),
			snd_pcm_sgbuf_get_addr(dma->substream, 0));
		break;
	}
	/*
	pr_debug( "vortex: cfg0 = 0x%x\nvortex: cfg1=0x%x\n",
	       dma->cfg0, dma->cfg1);
	*/
	hwwrite(vortex->mmio, VORTEX_ADBDMA_BUFCFG0 + (adbdma << 3), dma->cfg0);
	hwwrite(vortex->mmio, VORTEX_ADBDMA_BUFCFG1 + (adbdma << 3), dma->cfg1);

	vortex_adbdma_setfirstbuffer(vortex, adbdma);
	vortex_adbdma_setstartbuffer(vortex, adbdma, 0);
}