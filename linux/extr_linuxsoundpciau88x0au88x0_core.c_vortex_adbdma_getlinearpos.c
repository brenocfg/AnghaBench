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
struct TYPE_5__ {int nr_periods; int period_real; int period_virt; int period_bytes; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 int ADB_SUBBUF_MASK ; 
 int ADB_SUBBUF_SHIFT ; 
 scalar_t__ VORTEX_ADBDMA_STAT ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int vortex_adbdma_getlinearpos(vortex_t * vortex, int adbdma)
{
	stream_t *dma = &vortex->dma_adb[adbdma];
	int temp, page, delta;

	temp = hwread(vortex->mmio, VORTEX_ADBDMA_STAT + (adbdma << 2));
	page = (temp & ADB_SUBBUF_MASK) >> ADB_SUBBUF_SHIFT;
	if (dma->nr_periods >= 4)
		delta = (page - dma->period_real) & 3;
	else {
		delta = (page - dma->period_real);
		if (delta < 0)
			delta += dma->nr_periods;
	}
	return (dma->period_virt + delta) * dma->period_bytes
		+ (temp & (dma->period_bytes - 1));
}