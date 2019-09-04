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
struct slgt_info {int tx_enabled; int tx_active; int /*<<< orphan*/  tx_timer; } ;

/* Variables and functions */
 unsigned short BIT1 ; 
 unsigned short BIT2 ; 
 scalar_t__ IRQ_TXDATA ; 
 scalar_t__ IRQ_TXIDLE ; 
 scalar_t__ IRQ_TXUNDER ; 
 int /*<<< orphan*/  SSR ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tbufs (struct slgt_info*) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,scalar_t__) ; 
 int /*<<< orphan*/  tdma_reset (struct slgt_info*) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void tx_stop(struct slgt_info *info)
{
	unsigned short val;

	del_timer(&info->tx_timer);

	tdma_reset(info);

	/* reset and disable transmitter */
	val = rd_reg16(info, TCR) & ~BIT1;          /* clear enable bit */
	wr_reg16(info, TCR, (unsigned short)(val | BIT2)); /* set reset bit */

	slgt_irq_off(info, IRQ_TXDATA + IRQ_TXIDLE + IRQ_TXUNDER);

	/* clear tx idle and underrun status bit */
	wr_reg16(info, SSR, (unsigned short)(IRQ_TXIDLE + IRQ_TXUNDER));

	reset_tbufs(info);

	info->tx_enabled = false;
	info->tx_active = false;
}