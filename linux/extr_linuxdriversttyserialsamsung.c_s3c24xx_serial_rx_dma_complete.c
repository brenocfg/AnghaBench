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
struct uart_port {int /*<<< orphan*/  lock; TYPE_1__* state; } ;
struct tty_struct {int dummy; } ;
struct tty_port {int dummy; } ;
struct s3c24xx_uart_port {struct uart_port port; struct s3c24xx_uart_dma* dma; } ;
struct s3c24xx_uart_dma {int rx_bytes_requested; int /*<<< orphan*/  rx_desc; int /*<<< orphan*/  rx_cookie; int /*<<< orphan*/  rx_chan; } ;
struct dma_tx_state {int residue; } ;
struct TYPE_2__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  s3c24xx_uart_copy_rx_to_tty (struct s3c24xx_uart_port*,struct tty_port*,int) ; 
 int /*<<< orphan*/  s3c64xx_start_rx_dma (struct s3c24xx_uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 

__attribute__((used)) static void s3c24xx_serial_rx_dma_complete(void *args)
{
	struct s3c24xx_uart_port *ourport = args;
	struct uart_port *port = &ourport->port;

	struct s3c24xx_uart_dma *dma = ourport->dma;
	struct tty_port *t = &port->state->port;
	struct tty_struct *tty = tty_port_tty_get(&ourport->port.state->port);

	struct dma_tx_state state;
	unsigned long flags;
	int received;

	dmaengine_tx_status(dma->rx_chan,  dma->rx_cookie, &state);
	received  = dma->rx_bytes_requested - state.residue;
	async_tx_ack(dma->rx_desc);

	spin_lock_irqsave(&port->lock, flags);

	if (received)
		s3c24xx_uart_copy_rx_to_tty(ourport, t, received);

	if (tty) {
		tty_flip_buffer_push(t);
		tty_kref_put(tty);
	}

	s3c64xx_start_rx_dma(ourport);

	spin_unlock_irqrestore(&port->lock, flags);
}