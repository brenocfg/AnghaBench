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
struct msm_port {int /*<<< orphan*/  clk; scalar_t__ is_uartdm; scalar_t__ imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IMR ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  msm_release_dma (struct msm_port*) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_shutdown(struct uart_port *port)
{
	struct msm_port *msm_port = UART_TO_MSM(port);

	msm_port->imr = 0;
	msm_write(port, 0, UART_IMR); /* disable interrupts */

	if (msm_port->is_uartdm)
		msm_release_dma(msm_port);

	clk_disable_unprepare(msm_port->clk);

	free_irq(port->irq, port);
}