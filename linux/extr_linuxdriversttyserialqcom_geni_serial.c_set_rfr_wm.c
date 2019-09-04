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
struct qcom_geni_serial_port {int /*<<< orphan*/  tx_wm; int /*<<< orphan*/  rx_wm; scalar_t__ rx_fifo_depth; scalar_t__ rx_rfr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_TX_WM ; 
 int /*<<< orphan*/  UART_CONSOLE_RX_WM ; 

__attribute__((used)) static void set_rfr_wm(struct qcom_geni_serial_port *port)
{
	/*
	 * Set RFR (Flow off) to FIFO_DEPTH - 2.
	 * RX WM level at 10% RX_FIFO_DEPTH.
	 * TX WM level at 10% TX_FIFO_DEPTH.
	 */
	port->rx_rfr = port->rx_fifo_depth - 2;
	port->rx_wm = UART_CONSOLE_RX_WM;
	port->tx_wm = DEF_TX_WM;
}