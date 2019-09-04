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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int AML_UART_CLEAR_ERR ; 
 scalar_t__ AML_UART_CONTROL ; 
 int AML_UART_RX_RST ; 
 int AML_UART_TX_RST ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_uart_reset(struct uart_port *port)
{
	u32 val;

	val = readl(port->membase + AML_UART_CONTROL);
	val |= (AML_UART_RX_RST | AML_UART_TX_RST | AML_UART_CLEAR_ERR);
	writel(val, port->membase + AML_UART_CONTROL);

	val &= ~(AML_UART_RX_RST | AML_UART_TX_RST | AML_UART_CLEAR_ERR);
	writel(val, port->membase + AML_UART_CONTROL);
}