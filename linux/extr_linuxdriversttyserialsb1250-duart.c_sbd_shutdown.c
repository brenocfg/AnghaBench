#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct sbd_port {int tx_stopped; TYPE_1__ port; } ;

/* Variables and functions */
 int M_DUART_RX_DIS ; 
 int M_DUART_TX_DIS ; 
 int /*<<< orphan*/  R_DUART_CMD ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sbd_port*) ; 
 struct sbd_port* to_sport (struct uart_port*) ; 
 int /*<<< orphan*/  write_sbdchn (struct sbd_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sbd_shutdown(struct uart_port *uport)
{
	struct sbd_port *sport = to_sport(uport);

	write_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS | M_DUART_RX_DIS);
	sport->tx_stopped = 1;
	free_irq(sport->port.irq, sport);
}