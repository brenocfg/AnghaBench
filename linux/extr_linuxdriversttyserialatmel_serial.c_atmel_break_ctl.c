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
 int /*<<< orphan*/  ATMEL_US_CR ; 
 int /*<<< orphan*/  ATMEL_US_STPBRK ; 
 int /*<<< orphan*/  ATMEL_US_STTBRK ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_break_ctl(struct uart_port *port, int break_state)
{
	if (break_state != 0)
		/* start break */
		atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_STTBRK);
	else
		/* stop break */
		atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_STPBRK);
}