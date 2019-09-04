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
struct pic32_sport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_UART_MODE ; 
 int PIC32_UART_MODE_ON ; 
 int /*<<< orphan*/  PIC32_UART_STA ; 
 int PIC32_UART_STA_UTXEN ; 
 int /*<<< orphan*/  pic32_uart_irqtxen (struct pic32_sport*,int /*<<< orphan*/ ) ; 
 int pic32_uart_readl (struct pic32_sport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_uart_writel (struct pic32_sport*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pic32_wait_deplete_txbuf (struct pic32_sport*) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 

__attribute__((used)) static void pic32_uart_stop_tx(struct uart_port *port)
{
	struct pic32_sport *sport = to_pic32_sport(port);

	if (!(pic32_uart_readl(sport, PIC32_UART_MODE) & PIC32_UART_MODE_ON))
		return;

	if (!(pic32_uart_readl(sport, PIC32_UART_STA) & PIC32_UART_STA_UTXEN))
		return;

	/* wait for tx empty */
	pic32_wait_deplete_txbuf(sport);

	pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_STA),
				PIC32_UART_STA_UTXEN);
	pic32_uart_irqtxen(sport, 0);
}