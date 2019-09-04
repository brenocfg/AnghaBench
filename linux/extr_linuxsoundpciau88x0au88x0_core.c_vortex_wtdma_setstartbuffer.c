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
struct TYPE_5__ {int period_real; int period_virt; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 scalar_t__ VORTEX_WTDMA_START ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void vortex_wtdma_setstartbuffer(vortex_t * vortex, int wtdma, int sb)
{
	stream_t *dma = &vortex->dma_wt[wtdma];
	//hwwrite(vortex->mmio, VORTEX_WTDMA_START + (wtdma << 2), sb << ((0x1f-(wtdma&0xf)*2)));
	hwwrite(vortex->mmio, VORTEX_WTDMA_START + (wtdma << 2),
		sb << ((0xf - (wtdma & 0xf)) * 2));
	dma->period_real = dma->period_virt = sb;
}