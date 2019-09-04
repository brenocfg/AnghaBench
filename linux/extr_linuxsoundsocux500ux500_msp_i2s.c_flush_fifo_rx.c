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
 scalar_t__ MSP_DR ; 
 scalar_t__ MSP_FLR ; 
 scalar_t__ MSP_GCR ; 
 int RX_ENABLE ; 
 int RX_FIFO_EMPTY ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void flush_fifo_rx(struct ux500_msp *msp)
{
	u32 reg_val_DR, reg_val_GCR, reg_val_FLR;
	u32 limit = 32;

	reg_val_GCR = readl(msp->registers + MSP_GCR);
	writel(reg_val_GCR | RX_ENABLE, msp->registers + MSP_GCR);

	reg_val_FLR = readl(msp->registers + MSP_FLR);
	while (!(reg_val_FLR & RX_FIFO_EMPTY) && limit--) {
		reg_val_DR = readl(msp->registers + MSP_DR);
		reg_val_FLR = readl(msp->registers + MSP_FLR);
	}

	writel(reg_val_GCR, msp->registers + MSP_GCR);
}