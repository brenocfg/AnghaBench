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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct cas {unsigned long block_dvma; scalar_t__ regs; scalar_t__ init_block; scalar_t__* init_txds; } ;

/* Variables and functions */
 int CAS_TX_RINGN_BASE (int) ; 
 int MAX_TX_RINGS ; 
 scalar_t__ REG_TX_CFG ; 
 scalar_t__ REG_TX_DBN_HI (int) ; 
 scalar_t__ REG_TX_DBN_LOW (int) ; 
 scalar_t__ REG_TX_MAXBURST_0 ; 
 scalar_t__ REG_TX_MAXBURST_1 ; 
 scalar_t__ REG_TX_MAXBURST_2 ; 
 scalar_t__ REG_TX_MAXBURST_3 ; 
 int TX_CFG_COMPWB_Q1 ; 
 int TX_CFG_COMPWB_Q2 ; 
 int TX_CFG_COMPWB_Q3 ; 
 int TX_CFG_COMPWB_Q4 ; 
 int TX_CFG_DMA_RDPIPE_DIS ; 
 int TX_CFG_INTR_COMPWB_DIS ; 
 int TX_CFG_PACED_MODE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_init_tx_dma(struct cas *cp)
{
	u64 desc_dma = cp->block_dvma;
	unsigned long off;
	u32 val;
	int i;

	/* set up tx completion writeback registers. must be 8-byte aligned */
#ifdef USE_TX_COMPWB
	off = offsetof(struct cas_init_block, tx_compwb);
	writel((desc_dma + off) >> 32, cp->regs + REG_TX_COMPWB_DB_HI);
	writel((desc_dma + off) & 0xffffffff, cp->regs + REG_TX_COMPWB_DB_LOW);
#endif

	/* enable completion writebacks, enable paced mode,
	 * disable read pipe, and disable pre-interrupt compwbs
	 */
	val =   TX_CFG_COMPWB_Q1 | TX_CFG_COMPWB_Q2 |
		TX_CFG_COMPWB_Q3 | TX_CFG_COMPWB_Q4 |
		TX_CFG_DMA_RDPIPE_DIS | TX_CFG_PACED_MODE |
		TX_CFG_INTR_COMPWB_DIS;

	/* write out tx ring info and tx desc bases */
	for (i = 0; i < MAX_TX_RINGS; i++) {
		off = (unsigned long) cp->init_txds[i] -
			(unsigned long) cp->init_block;

		val |= CAS_TX_RINGN_BASE(i);
		writel((desc_dma + off) >> 32, cp->regs + REG_TX_DBN_HI(i));
		writel((desc_dma + off) & 0xffffffff, cp->regs +
		       REG_TX_DBN_LOW(i));
		/* don't zero out the kick register here as the system
		 * will wedge
		 */
	}
	writel(val, cp->regs + REG_TX_CFG);

	/* program max burst sizes. these numbers should be different
	 * if doing QoS.
	 */
#ifdef USE_QOS
	writel(0x800, cp->regs + REG_TX_MAXBURST_0);
	writel(0x1600, cp->regs + REG_TX_MAXBURST_1);
	writel(0x2400, cp->regs + REG_TX_MAXBURST_2);
	writel(0x4800, cp->regs + REG_TX_MAXBURST_3);
#else
	writel(0x800, cp->regs + REG_TX_MAXBURST_0);
	writel(0x800, cp->regs + REG_TX_MAXBURST_1);
	writel(0x800, cp->regs + REG_TX_MAXBURST_2);
	writel(0x800, cp->regs + REG_TX_MAXBURST_3);
#endif
}