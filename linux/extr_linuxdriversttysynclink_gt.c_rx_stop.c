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
struct slgt_info {int rx_enabled; int rx_restart; } ;

/* Variables and functions */
 unsigned short BIT1 ; 
 unsigned short BIT2 ; 
 scalar_t__ IRQ_RXDATA ; 
 unsigned short IRQ_RXIDLE ; 
 unsigned short IRQ_RXOVER ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  SSR ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_reset (struct slgt_info*) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,scalar_t__) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void rx_stop(struct slgt_info *info)
{
	unsigned short val;

	/* disable and reset receiver */
	val = rd_reg16(info, RCR) & ~BIT1;          /* clear enable bit */
	wr_reg16(info, RCR, (unsigned short)(val | BIT2)); /* set reset bit */
	wr_reg16(info, RCR, val);                  /* clear reset bit */

	slgt_irq_off(info, IRQ_RXOVER + IRQ_RXDATA + IRQ_RXIDLE);

	/* clear pending rx interrupts */
	wr_reg16(info, SSR, IRQ_RXIDLE + IRQ_RXOVER);

	rdma_reset(info);

	info->rx_enabled = false;
	info->rx_restart = false;
}