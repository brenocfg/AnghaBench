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
struct pic32_sport {int /*<<< orphan*/  irq_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_UART_STA ; 
 int /*<<< orphan*/  PIC32_UART_STA_URXEN ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_uart_writel (struct pic32_sport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 

__attribute__((used)) static void pic32_uart_stop_rx(struct uart_port *port)
{
	struct pic32_sport *sport = to_pic32_sport(port);

	/* disable rx interrupts */
	disable_irq(sport->irq_rx);

	/* receiver Enable bit OFF */
	pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_STA),
				PIC32_UART_STA_URXEN);
}