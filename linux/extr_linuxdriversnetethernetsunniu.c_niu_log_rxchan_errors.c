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
struct rx_ring_info {int /*<<< orphan*/  rx_channel; } ;
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RX_DMA_CTL_STAT_BYTE_EN_BUS ; 
 int RX_DMA_CTL_STAT_CFIGLOGPAGE ; 
 int RX_DMA_CTL_STAT_CONFIG_ERR ; 
 int RX_DMA_CTL_STAT_DC_FIFO_ERR ; 
 int RX_DMA_CTL_STAT_RBRFULL ; 
 int RX_DMA_CTL_STAT_RBRLOGPAGE ; 
 int RX_DMA_CTL_STAT_RBR_PRE_PAR ; 
 int RX_DMA_CTL_STAT_RBR_TMOUT ; 
 int RX_DMA_CTL_STAT_RCRFULL ; 
 int RX_DMA_CTL_STAT_RCRINCON ; 
 int RX_DMA_CTL_STAT_RCR_ACK_ERR ; 
 int RX_DMA_CTL_STAT_RCR_SHA_PAR ; 
 int RX_DMA_CTL_STAT_RSP_CNT_ERR ; 
 int RX_DMA_CTL_STAT_RSP_DAT_ERR ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void niu_log_rxchan_errors(struct niu *np, struct rx_ring_info *rp,
				  u64 stat)
{
	netdev_err(np->dev, "RX channel %u errors ( ", rp->rx_channel);

	if (stat & RX_DMA_CTL_STAT_RBR_TMOUT)
		pr_cont("RBR_TMOUT ");
	if (stat & RX_DMA_CTL_STAT_RSP_CNT_ERR)
		pr_cont("RSP_CNT ");
	if (stat & RX_DMA_CTL_STAT_BYTE_EN_BUS)
		pr_cont("BYTE_EN_BUS ");
	if (stat & RX_DMA_CTL_STAT_RSP_DAT_ERR)
		pr_cont("RSP_DAT ");
	if (stat & RX_DMA_CTL_STAT_RCR_ACK_ERR)
		pr_cont("RCR_ACK ");
	if (stat & RX_DMA_CTL_STAT_RCR_SHA_PAR)
		pr_cont("RCR_SHA_PAR ");
	if (stat & RX_DMA_CTL_STAT_RBR_PRE_PAR)
		pr_cont("RBR_PRE_PAR ");
	if (stat & RX_DMA_CTL_STAT_CONFIG_ERR)
		pr_cont("CONFIG ");
	if (stat & RX_DMA_CTL_STAT_RCRINCON)
		pr_cont("RCRINCON ");
	if (stat & RX_DMA_CTL_STAT_RCRFULL)
		pr_cont("RCRFULL ");
	if (stat & RX_DMA_CTL_STAT_RBRFULL)
		pr_cont("RBRFULL ");
	if (stat & RX_DMA_CTL_STAT_RBRLOGPAGE)
		pr_cont("RBRLOGPAGE ");
	if (stat & RX_DMA_CTL_STAT_CFIGLOGPAGE)
		pr_cont("CFIGLOGPAGE ");
	if (stat & RX_DMA_CTL_STAT_DC_FIFO_ERR)
		pr_cont("DC_FIDO ");

	pr_cont(")\n");
}