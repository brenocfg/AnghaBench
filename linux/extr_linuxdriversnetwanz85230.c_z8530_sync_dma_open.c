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
struct z8530_channel {int sync; int mtu; int rxdma_on; int txdma_on; int tx_dma_used; int dma_tx; int dma_ready; int* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * irqs; int /*<<< orphan*/  txdma; int /*<<< orphan*/  rxdma; int /*<<< orphan*/ ** rx_buf; scalar_t__ dma_num; int /*<<< orphan*/ ** tx_dma_buf; int /*<<< orphan*/ * skb2; int /*<<< orphan*/ * skb; scalar_t__ count; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int DMA_MODE_READ ; 
 int DMA_MODE_WRITE ; 
 int DTRREQ ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int INT_ERR_Rx ; 
 int PAGE_SIZE ; 
 size_t R1 ; 
 size_t R14 ; 
 size_t R3 ; 
 int RxENABLE ; 
 int TxINT_ENAB ; 
 int WT_FN_RDYFN ; 
 int WT_RDY_ENAB ; 
 int WT_RDY_RT ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,size_t,int) ; 
 int /*<<< orphan*/  z8530_dma_sync ; 
 int /*<<< orphan*/  z8530_rtsdtr (struct z8530_channel*,int) ; 

int z8530_sync_dma_open(struct net_device *dev, struct z8530_channel *c)
{
	unsigned long cflags, dflags;
	
	c->sync = 1;
	c->mtu = dev->mtu+64;
	c->count = 0;
	c->skb = NULL;
	c->skb2 = NULL;
	/*
	 *	Load the DMA interfaces up
	 */
	c->rxdma_on = 0;
	c->txdma_on = 0;
	
	/*
	 *	Allocate the DMA flip buffers. Limit by page size.
	 *	Everyone runs 1500 mtu or less on wan links so this
	 *	should be fine.
	 */
	 
	if(c->mtu  > PAGE_SIZE/2)
		return -EMSGSIZE;
	 
	c->rx_buf[0]=(void *)get_zeroed_page(GFP_KERNEL|GFP_DMA);
	if(c->rx_buf[0]==NULL)
		return -ENOBUFS;
	c->rx_buf[1]=c->rx_buf[0]+PAGE_SIZE/2;
	
	c->tx_dma_buf[0]=(void *)get_zeroed_page(GFP_KERNEL|GFP_DMA);
	if(c->tx_dma_buf[0]==NULL)
	{
		free_page((unsigned long)c->rx_buf[0]);
		c->rx_buf[0]=NULL;
		return -ENOBUFS;
	}
	c->tx_dma_buf[1]=c->tx_dma_buf[0]+PAGE_SIZE/2;

	c->tx_dma_used=0;
	c->dma_tx = 1;
	c->dma_num=0;
	c->dma_ready=1;
	
	/*
	 *	Enable DMA control mode
	 */

	spin_lock_irqsave(c->lock, cflags);
	 
	/*
	 *	TX DMA via DIR/REQ
	 */
	 
	c->regs[R14]|= DTRREQ;
	write_zsreg(c, R14, c->regs[R14]);     

	c->regs[R1]&= ~TxINT_ENAB;
	write_zsreg(c, R1, c->regs[R1]);
	
	/*
	 *	RX DMA via W/Req
	 */	 

	c->regs[R1]|= WT_FN_RDYFN;
	c->regs[R1]|= WT_RDY_RT;
	c->regs[R1]|= INT_ERR_Rx;
	c->regs[R1]&= ~TxINT_ENAB;
	write_zsreg(c, R1, c->regs[R1]);
	c->regs[R1]|= WT_RDY_ENAB;
	write_zsreg(c, R1, c->regs[R1]);            
	
	/*
	 *	DMA interrupts
	 */
	 
	/*
	 *	Set up the DMA configuration
	 */	
	 
	dflags=claim_dma_lock();
	 
	disable_dma(c->rxdma);
	clear_dma_ff(c->rxdma);
	set_dma_mode(c->rxdma, DMA_MODE_READ|0x10);
	set_dma_addr(c->rxdma, virt_to_bus(c->rx_buf[0]));
	set_dma_count(c->rxdma, c->mtu);
	enable_dma(c->rxdma);

	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	set_dma_mode(c->txdma, DMA_MODE_WRITE);
	disable_dma(c->txdma);
	
	release_dma_lock(dflags);
	
	/*
	 *	Select the DMA interrupt handlers
	 */

	c->rxdma_on = 1;
	c->txdma_on = 1;
	c->tx_dma_used = 1;
	 
	c->irqs = &z8530_dma_sync;
	z8530_rtsdtr(c,1);
	write_zsreg(c, R3, c->regs[R3]|RxENABLE);

	spin_unlock_irqrestore(c->lock, cflags);
	
	return 0;
}