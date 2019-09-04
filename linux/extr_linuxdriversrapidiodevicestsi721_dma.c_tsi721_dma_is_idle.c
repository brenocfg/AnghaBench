#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct tsi721_bdma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TSI721_DMAC_STS ; 
 int TSI721_DMAC_STS_RUN ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static bool tsi721_dma_is_idle(struct tsi721_bdma_chan *bdma_chan)
{
	u32 sts;

	sts = ioread32(bdma_chan->regs + TSI721_DMAC_STS);
	return ((sts & TSI721_DMAC_STS_RUN) == 0);
}