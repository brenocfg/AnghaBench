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
struct ar933x_uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 unsigned int AR933X_UART_DATA_TX_CSR ; 
 int AR933X_UART_DATA_TX_RX_MASK ; 
 int /*<<< orphan*/  ar933x_uart_write (struct ar933x_uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void ar933x_uart_putc(struct ar933x_uart_port *up, int ch)
{
	unsigned int rdata;

	rdata = ch & AR933X_UART_DATA_TX_RX_MASK;
	rdata |= AR933X_UART_DATA_TX_CSR;
	ar933x_uart_write(up, AR933X_UART_DATA_REG, rdata);
}