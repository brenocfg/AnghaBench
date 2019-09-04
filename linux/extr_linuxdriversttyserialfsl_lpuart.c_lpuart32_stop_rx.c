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
 int /*<<< orphan*/  UARTCTRL ; 
 unsigned long UARTCTRL_RE ; 
 unsigned long lpuart32_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_write (struct uart_port*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpuart32_stop_rx(struct uart_port *port)
{
	unsigned long temp;

	temp = lpuart32_read(port, UARTCTRL);
	lpuart32_write(port, temp & ~UARTCTRL_RE, UARTCTRL);
}