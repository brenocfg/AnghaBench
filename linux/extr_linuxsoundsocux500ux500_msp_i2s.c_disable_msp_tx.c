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
struct ux500_msp {int /*<<< orphan*/  dir_busy; scalar_t__ registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_DIR_TX ; 
 scalar_t__ MSP_DMACR ; 
 scalar_t__ MSP_GCR ; 
 scalar_t__ MSP_IMSC ; 
 int TX_DMA_ENABLE ; 
 int TX_ENABLE ; 
 int TX_SERVICE_INT ; 
 int TX_UNDERRUN_ERR_INT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void disable_msp_tx(struct ux500_msp *msp)
{
	u32 reg_val_GCR, reg_val_DMACR, reg_val_IMSC;

	reg_val_GCR = readl(msp->registers + MSP_GCR);
	writel(reg_val_GCR & ~TX_ENABLE, msp->registers + MSP_GCR);
	reg_val_DMACR = readl(msp->registers + MSP_DMACR);
	writel(reg_val_DMACR & ~TX_DMA_ENABLE, msp->registers + MSP_DMACR);
	reg_val_IMSC = readl(msp->registers + MSP_IMSC);
	writel(reg_val_IMSC &
			~(TX_SERVICE_INT | TX_UNDERRUN_ERR_INT),
			msp->registers + MSP_IMSC);

	msp->dir_busy &= ~MSP_DIR_TX;
}