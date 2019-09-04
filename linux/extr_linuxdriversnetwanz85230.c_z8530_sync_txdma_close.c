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
typedef  int /*<<< orphan*/  u8 ;
struct z8530_channel {int* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** tx_dma_buf; scalar_t__ tx_dma_used; scalar_t__ txdma_on; int /*<<< orphan*/  txdma; scalar_t__ sync; scalar_t__ max; int /*<<< orphan*/ * irqs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int DTRREQ ; 
 int INT_ALL_Rx ; 
 int INT_ERR_Rx ; 
 int /*<<< orphan*/  R0 ; 
 size_t R1 ; 
 size_t R14 ; 
 size_t R3 ; 
 int WT_FN_RDYFN ; 
 int WT_RDY_ENAB ; 
 int WT_RDY_RT ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,size_t,int) ; 
 int /*<<< orphan*/  z8530_nop ; 
 int /*<<< orphan*/  z8530_rtsdtr (struct z8530_channel*,int /*<<< orphan*/ ) ; 

int z8530_sync_txdma_close(struct net_device *dev, struct z8530_channel *c)
{
	unsigned long dflags, cflags;
	u8 chk;

	
	spin_lock_irqsave(c->lock, cflags);
	
	c->irqs = &z8530_nop;
	c->max = 0;
	c->sync = 0;
	
	/*
	 *	Disable the PC DMA channels
	 */
	 
	dflags = claim_dma_lock();

	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	c->txdma_on = 0;
	c->tx_dma_used = 0;

	release_dma_lock(dflags);

	/*
	 *	Disable DMA control mode
	 */
	 
	c->regs[R1]&= ~WT_RDY_ENAB;
	write_zsreg(c, R1, c->regs[R1]);            
	c->regs[R1]&= ~(WT_RDY_RT|WT_FN_RDYFN|INT_ERR_Rx);
	c->regs[R1]|= INT_ALL_Rx;
	write_zsreg(c, R1, c->regs[R1]);
	c->regs[R14]&= ~DTRREQ;
	write_zsreg(c, R14, c->regs[R14]);   
	
	if(c->tx_dma_buf[0])
	{
		free_page((unsigned long)c->tx_dma_buf[0]);
		c->tx_dma_buf[0]=NULL;
	}
	chk=read_zsreg(c,R0);
	write_zsreg(c, R3, c->regs[R3]);
	z8530_rtsdtr(c,0);

	spin_unlock_irqrestore(c->lock, cflags);
	return 0;
}