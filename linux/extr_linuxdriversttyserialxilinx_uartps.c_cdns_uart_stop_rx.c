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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ CDNS_UART_CR ; 
 unsigned int CDNS_UART_CR_RX_DIS ; 
 scalar_t__ CDNS_UART_IDR ; 
 unsigned int CDNS_UART_RX_IRQS ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void cdns_uart_stop_rx(struct uart_port *port)
{
	unsigned int regval;

	/* Disable RX IRQs */
	writel(CDNS_UART_RX_IRQS, port->membase + CDNS_UART_IDR);

	/* Disable the receiver */
	regval = readl(port->membase + CDNS_UART_CR);
	regval |= CDNS_UART_CR_RX_DIS;
	writel(regval, port->membase + CDNS_UART_CR);
}