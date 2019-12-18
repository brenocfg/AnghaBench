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

/* Variables and functions */
 scalar_t__ DMA_CTRL_STATUS ; 
 scalar_t__ SATA_DMA_REGS_BASE ; 
 unsigned int encode_start (unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void dma_start(void)
{
	unsigned int reg;
	reg = readl(SATA_DMA_REGS_BASE + DMA_CTRL_STATUS);
	reg = encode_start(reg);
	writel(reg, SATA_DMA_REGS_BASE + DMA_CTRL_STATUS);
}