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
typedef  int u8 ;
typedef  int u32 ;
struct sprd_mcdt_dev {int base; } ;

/* Variables and functions */
 int MCDT_ADC0_FIFO_ADDR_ST ; 
 int MCDT_CH_FIFO_ADDR_MASK ; 
 int MCDT_CH_FIFO_ADDR_SHIFT ; 
 int MCDT_FIFO_LENGTH ; 
 int readl_relaxed (int) ; 

__attribute__((used)) static u32 sprd_mcdt_adc_fifo_avail(struct sprd_mcdt_dev *mcdt, u8 channel)
{
	u32 reg = MCDT_ADC0_FIFO_ADDR_ST + channel * 8;
	u32 r_addr = (readl_relaxed(mcdt->base + reg) >>
		      MCDT_CH_FIFO_ADDR_SHIFT) & MCDT_CH_FIFO_ADDR_MASK;
	u32 w_addr = readl_relaxed(mcdt->base + reg) & MCDT_CH_FIFO_ADDR_MASK;

	if (w_addr >= r_addr)
		return 4 * (w_addr - r_addr);
	else
		return 4 * (MCDT_FIFO_LENGTH - r_addr + w_addr);
}