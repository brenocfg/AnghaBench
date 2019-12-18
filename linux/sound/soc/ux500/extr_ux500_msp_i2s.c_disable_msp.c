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
struct ux500_msp {scalar_t__ registers; } ;

/* Variables and functions */
 int LOOPBACK_MASK ; 
 unsigned int MSP_DIR_TX ; 
 scalar_t__ MSP_GCR ; 
 int RX_ENABLE ; 
 int TX_ENABLE ; 
 int /*<<< orphan*/  disable_msp_rx (struct ux500_msp*) ; 
 int /*<<< orphan*/  disable_msp_tx (struct ux500_msp*) ; 
 int /*<<< orphan*/  flush_fifo_rx (struct ux500_msp*) ; 
 int /*<<< orphan*/  flush_fifo_tx (struct ux500_msp*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int disable_msp(struct ux500_msp *msp, unsigned int dir)
{
	u32 reg_val_GCR;
	int status = 0;
	unsigned int disable_tx, disable_rx;

	reg_val_GCR = readl(msp->registers + MSP_GCR);
	disable_tx = dir & MSP_DIR_TX;
	disable_rx = dir & MSP_DIR_TX;
	if (disable_tx && disable_rx) {
		reg_val_GCR = readl(msp->registers + MSP_GCR);
		writel(reg_val_GCR | LOOPBACK_MASK,
				msp->registers + MSP_GCR);

		/* Flush TX-FIFO */
		flush_fifo_tx(msp);

		/* Disable TX-channel */
		writel((readl(msp->registers + MSP_GCR) &
			       (~TX_ENABLE)), msp->registers + MSP_GCR);

		/* Flush RX-FIFO */
		flush_fifo_rx(msp);

		/* Disable Loopback and Receive channel */
		writel((readl(msp->registers + MSP_GCR) &
				(~(RX_ENABLE | LOOPBACK_MASK))),
				msp->registers + MSP_GCR);

		disable_msp_tx(msp);
		disable_msp_rx(msp);
	} else if (disable_tx)
		disable_msp_tx(msp);
	else if (disable_rx)
		disable_msp_rx(msp);

	return status;
}