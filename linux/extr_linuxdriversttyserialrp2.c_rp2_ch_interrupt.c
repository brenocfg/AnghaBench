#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* state; } ;
struct rp2_uart_port {TYPE_3__ port; scalar_t__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ RP2_CHAN_STAT ; 
 int RP2_CHAN_STAT_MS_CHANGED_MASK ; 
 int RP2_CHAN_STAT_RXDATA_m ; 
 int RP2_CHAN_STAT_TXEMPTY_m ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rp2_rx_chars (struct rp2_uart_port*) ; 
 int /*<<< orphan*/  rp2_tx_chars (struct rp2_uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void rp2_ch_interrupt(struct rp2_uart_port *up)
{
	u32 status;

	spin_lock(&up->port.lock);

	/*
	 * The IRQ status bits are clear-on-write.  Other status bits in
	 * this register aren't, so it's harmless to write to them.
	 */
	status = readl(up->base + RP2_CHAN_STAT);
	writel(status, up->base + RP2_CHAN_STAT);

	if (status & RP2_CHAN_STAT_RXDATA_m)
		rp2_rx_chars(up);
	if (status & RP2_CHAN_STAT_TXEMPTY_m)
		rp2_tx_chars(up);
	if (status & RP2_CHAN_STAT_MS_CHANGED_MASK)
		wake_up_interruptible(&up->port.state->port.delta_msr_wait);

	spin_unlock(&up->port.lock);
}