#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* dma_adb; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_6__ {scalar_t__ fifo_status; scalar_t__ fifo_enabled; int /*<<< orphan*/  dma_unknown; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 scalar_t__ FIFO_START ; 
 scalar_t__ FIFO_STOP ; 
 int /*<<< orphan*/  vortex_fifo_setadbctrl (TYPE_1__*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_adbdma_stopfifo(vortex_t * vortex, int adbdma)
{
	stream_t *dma = &vortex->dma_adb[adbdma];

	int this_4 = 0, this_8 = 0;
	if (dma->fifo_status == FIFO_START)
		vortex_fifo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
	else if (dma->fifo_status == FIFO_STOP)
		return;
	dma->fifo_status = FIFO_STOP;
	dma->fifo_enabled = 0;
}