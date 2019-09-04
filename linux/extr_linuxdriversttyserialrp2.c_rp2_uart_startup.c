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
struct uart_port {int dummy; } ;
struct rp2_uart_port {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP2_CHAN_STAT ; 
 int /*<<< orphan*/  RP2_TXRX_CTL ; 
 int /*<<< orphan*/  RP2_TXRX_CTL_MSRIRQ_m ; 
 int /*<<< orphan*/  RP2_TXRX_CTL_RXIRQ_m ; 
 int /*<<< orphan*/  RP2_TXRX_CTL_RX_TRIG_1 ; 
 int /*<<< orphan*/  RP2_TXRX_CTL_RX_TRIG_m ; 
 struct rp2_uart_port* port_to_up (struct uart_port*) ; 
 int /*<<< orphan*/  rp2_flush_fifos (struct rp2_uart_port*) ; 
 int /*<<< orphan*/  rp2_mask_ch_irq (struct rp2_uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rp2_rmw (struct rp2_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rp2_uart_startup(struct uart_port *port)
{
	struct rp2_uart_port *up = port_to_up(port);

	rp2_flush_fifos(up);
	rp2_rmw(up, RP2_TXRX_CTL, RP2_TXRX_CTL_MSRIRQ_m, RP2_TXRX_CTL_RXIRQ_m);
	rp2_rmw(up, RP2_TXRX_CTL, RP2_TXRX_CTL_RX_TRIG_m,
		RP2_TXRX_CTL_RX_TRIG_1);
	rp2_rmw(up, RP2_CHAN_STAT, 0, 0);
	rp2_mask_ch_irq(up, up->idx, 1);

	return 0;
}