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
typedef  int u64 ;
struct rx_ring_info {int rx_channel; int mbox_dma; int rbr_dma; int rcr_dma; int rbr_index; scalar_t__ rcr_timeout; scalar_t__ rcr_pkt_threshold; scalar_t__ rcr_table_size; scalar_t__ rbr_table_size; } ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBR_CFIG_A (int) ; 
 int RBR_CFIG_A_LEN_SHIFT ; 
 int RBR_CFIG_A_STADDR ; 
 int RBR_CFIG_A_STADDR_BASE ; 
 int /*<<< orphan*/  RBR_CFIG_B (int) ; 
 int /*<<< orphan*/  RBR_KICK (int) ; 
 int /*<<< orphan*/  RCRCFIG_A (int) ; 
 int RCRCFIG_A_LEN_SHIFT ; 
 int RCRCFIG_A_STADDR ; 
 int RCRCFIG_A_STADDR_BASE ; 
 int /*<<< orphan*/  RCRCFIG_B (int) ; 
 int RCRCFIG_B_ENTOUT ; 
 int RCRCFIG_B_PTHRES_SHIFT ; 
 int RCRCFIG_B_TIMEOUT_SHIFT ; 
 int /*<<< orphan*/  RXDMA_CFIG1 (int) ; 
 int /*<<< orphan*/  RXDMA_CFIG2 (int) ; 
 int RXDMA_CFIG2_FULL_HDR ; 
 int RXDMA_CFIG2_MBADDR_L ; 
 int /*<<< orphan*/  RX_DMA_CTL_STAT (int) ; 
 int RX_DMA_CTL_STAT_MEX ; 
 int RX_DMA_CTL_STAT_RBR_EMPTY ; 
 int RX_DMA_CTL_STAT_RCRTHRES ; 
 int RX_DMA_CTL_STAT_RCRTO ; 
 int /*<<< orphan*/  RX_DMA_ENT_MSK (int) ; 
 int RX_DMA_ENT_MSK_RBR_EMPTY ; 
 int niu_compute_rbr_cfig_b (struct rx_ring_info*,int*) ; 
 int niu_enable_rx_channel (struct niu*,int,int) ; 
 int niu_rx_channel_lpage_init (struct niu*,int) ; 
 int niu_rx_channel_reset (struct niu*,int) ; 
 int /*<<< orphan*/  niu_rx_channel_wred_init (struct niu*,struct rx_ring_info*) ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_init_one_rx_channel(struct niu *np, struct rx_ring_info *rp)
{
	int err, channel = rp->rx_channel;
	u64 val;

	err = niu_rx_channel_reset(np, channel);
	if (err)
		return err;

	err = niu_rx_channel_lpage_init(np, channel);
	if (err)
		return err;

	niu_rx_channel_wred_init(np, rp);

	nw64(RX_DMA_ENT_MSK(channel), RX_DMA_ENT_MSK_RBR_EMPTY);
	nw64(RX_DMA_CTL_STAT(channel),
	     (RX_DMA_CTL_STAT_MEX |
	      RX_DMA_CTL_STAT_RCRTHRES |
	      RX_DMA_CTL_STAT_RCRTO |
	      RX_DMA_CTL_STAT_RBR_EMPTY));
	nw64(RXDMA_CFIG1(channel), rp->mbox_dma >> 32);
	nw64(RXDMA_CFIG2(channel),
	     ((rp->mbox_dma & RXDMA_CFIG2_MBADDR_L) |
	      RXDMA_CFIG2_FULL_HDR));
	nw64(RBR_CFIG_A(channel),
	     ((u64)rp->rbr_table_size << RBR_CFIG_A_LEN_SHIFT) |
	     (rp->rbr_dma & (RBR_CFIG_A_STADDR_BASE | RBR_CFIG_A_STADDR)));
	err = niu_compute_rbr_cfig_b(rp, &val);
	if (err)
		return err;
	nw64(RBR_CFIG_B(channel), val);
	nw64(RCRCFIG_A(channel),
	     ((u64)rp->rcr_table_size << RCRCFIG_A_LEN_SHIFT) |
	     (rp->rcr_dma & (RCRCFIG_A_STADDR_BASE | RCRCFIG_A_STADDR)));
	nw64(RCRCFIG_B(channel),
	     ((u64)rp->rcr_pkt_threshold << RCRCFIG_B_PTHRES_SHIFT) |
	     RCRCFIG_B_ENTOUT |
	     ((u64)rp->rcr_timeout << RCRCFIG_B_TIMEOUT_SHIFT));

	err = niu_enable_rx_channel(np, channel, 1);
	if (err)
		return err;

	nw64(RBR_KICK(channel), rp->rbr_index);

	val = nr64(RX_DMA_CTL_STAT(channel));
	val |= RX_DMA_CTL_STAT_RBR_EMPTY;
	nw64(RX_DMA_CTL_STAT(channel), val);

	return 0;
}