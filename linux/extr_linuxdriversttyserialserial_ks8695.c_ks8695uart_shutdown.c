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
 int /*<<< orphan*/  KS8695_IRQ_UART_LINE_STATUS ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_MODEM_STATUS ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_RX ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_TX ; 
 int UART_GET_FCR (struct uart_port*) ; 
 int UART_GET_LCR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_FCR (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_LCR (struct uart_port*,int) ; 
 int URFC_URFE ; 
 int URLC_URSBC ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static void ks8695uart_shutdown(struct uart_port *port)
{
	/*
	 * Free the interrupt
	 */
	free_irq(KS8695_IRQ_UART_RX, port);
	free_irq(KS8695_IRQ_UART_TX, port);
	free_irq(KS8695_IRQ_UART_MODEM_STATUS, port);
	free_irq(KS8695_IRQ_UART_LINE_STATUS, port);

	/* disable break condition and fifos */
	UART_PUT_LCR(port, UART_GET_LCR(port) & ~URLC_URSBC);
	UART_PUT_FCR(port, UART_GET_FCR(port) & ~URFC_URFE);
}