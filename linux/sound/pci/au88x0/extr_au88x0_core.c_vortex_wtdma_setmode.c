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
struct TYPE_4__ {int /*<<< orphan*/  mmio; TYPE_2__* dma_wt; } ;
typedef  TYPE_1__ vortex_t ;
typedef  int u32 ;
struct TYPE_5__ {int dma_unknown; int dma_ctrl; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 int DIR_SHIFT ; 
 int FMT_MASK ; 
 int FMT_SHIFT ; 
 int IE_MASK ; 
 int IE_SHIFT ; 
 int OFFSET_MASK ; 
 scalar_t__ VORTEX_WTDMA_CTRL ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
vortex_wtdma_setmode(vortex_t * vortex, int wtdma, int ie, int fmt, int d,
		     /*int e, */ u32 offset)
{
	stream_t *dma = &vortex->dma_wt[wtdma];

	//dma->this_08 = e;
	dma->dma_unknown = d;
	dma->dma_ctrl = 0;
	dma->dma_ctrl =
	    ((offset & OFFSET_MASK) | (dma->dma_ctrl & ~OFFSET_MASK));
	/* PCMOUT interrupt */
	dma->dma_ctrl =
	    (dma->dma_ctrl & ~IE_MASK) | ((ie << IE_SHIFT) & IE_MASK);
	/* Always playback. */
	dma->dma_ctrl |= (1 << DIR_SHIFT);
	/* Audio Format */
	dma->dma_ctrl =
	    (dma->dma_ctrl & FMT_MASK) | ((fmt << FMT_SHIFT) & FMT_MASK);
	/* Write into hardware */
	hwwrite(vortex->mmio, VORTEX_WTDMA_CTRL + (wtdma << 2), dma->dma_ctrl);
}