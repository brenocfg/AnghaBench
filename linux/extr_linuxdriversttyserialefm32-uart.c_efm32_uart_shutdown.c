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
struct uart_port {int /*<<< orphan*/  irq; } ;
struct efm32_uart_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTn_IEN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_uart_write32 (struct efm32_uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct efm32_uart_port*) ; 
 struct efm32_uart_port* to_efm_port (struct uart_port*) ; 

__attribute__((used)) static void efm32_uart_shutdown(struct uart_port *port)
{
	struct efm32_uart_port *efm_port = to_efm_port(port);

	efm32_uart_write32(efm_port, 0, UARTn_IEN);
	free_irq(port->irq, efm_port);

	clk_disable(efm_port->clk);
}