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

/* Variables and functions */
 int /*<<< orphan*/  UART_IR_REG ; 
 unsigned int UART_IR_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_IR_TXEMPTY ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int bcm_uart_tx_empty(struct uart_port *port)
{
	unsigned int val;

	val = bcm_uart_readl(port, UART_IR_REG);
	return (val & UART_IR_STAT(UART_IR_TXEMPTY)) ? 1 : 0;
}