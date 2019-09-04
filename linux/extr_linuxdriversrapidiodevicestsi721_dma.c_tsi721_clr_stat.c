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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct tsi721_bdma_chan {int sts_rdptr; int sts_size; scalar_t__ regs; scalar_t__* sts_base; } ;

/* Variables and functions */
 scalar_t__ TSI721_DMAC_DSRP ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void tsi721_clr_stat(struct tsi721_bdma_chan *bdma_chan)
{
	u32 srd_ptr;
	u64 *sts_ptr;
	int i, j;

	/* Check and clear descriptor status FIFO entries */
	srd_ptr = bdma_chan->sts_rdptr;
	sts_ptr = bdma_chan->sts_base;
	j = srd_ptr * 8;
	while (sts_ptr[j]) {
		for (i = 0; i < 8 && sts_ptr[j]; i++, j++)
			sts_ptr[j] = 0;

		++srd_ptr;
		srd_ptr %= bdma_chan->sts_size;
		j = srd_ptr * 8;
	}

	iowrite32(srd_ptr, bdma_chan->regs + TSI721_DMAC_DSRP);
	bdma_chan->sts_rdptr = srd_ptr;
}