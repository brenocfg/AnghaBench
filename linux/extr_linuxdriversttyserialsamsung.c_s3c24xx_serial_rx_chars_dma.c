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
struct s3c24xx_uart_port {scalar_t__ rx_mode; struct uart_port port; struct s3c24xx_uart_dma* dma; } ;
struct s3c24xx_uart_dma {unsigned int rx_bytes_requested; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  rx_cookie; } ;
struct dma_tx_state {unsigned int residue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  S3C2410_UFSTAT ; 
 int /*<<< orphan*/  S3C2410_UTRSTAT ; 
 unsigned int S3C2410_UTRSTAT_TIMEOUT ; 
 scalar_t__ S3C24XX_RX_DMA ; 
 scalar_t__ S3C24XX_RX_PIO ; 
 int /*<<< orphan*/  dmaengine_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  enable_rx_dma (struct s3c24xx_uart_port*) ; 
 int /*<<< orphan*/  enable_rx_pio (struct s3c24xx_uart_port*) ; 
 unsigned int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c24xx_serial_rx_drain_fifo (struct s3c24xx_uart_port*) ; 
 int /*<<< orphan*/  s3c24xx_uart_copy_rx_to_tty (struct s3c24xx_uart_port*,struct tty_port*,unsigned int) ; 
 int /*<<< orphan*/  s3c64xx_start_rx_dma (struct s3c24xx_uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t s3c24xx_serial_rx_chars_dma(void *dev_id)
{
	unsigned int utrstat, ufstat, received;
	struct s3c24xx_uart_port *ourport = dev_id;
	struct uart_port *port = &ourport->port;
	struct s3c24xx_uart_dma *dma = ourport->dma;
	struct tty_struct *tty = tty_port_tty_get(&ourport->port.state->port);
	struct tty_port *t = &port->state->port;
	unsigned long flags;
	struct dma_tx_state state;

	utrstat = rd_regl(port, S3C2410_UTRSTAT);
	ufstat = rd_regl(port, S3C2410_UFSTAT);

	spin_lock_irqsave(&port->lock, flags);

	if (!(utrstat & S3C2410_UTRSTAT_TIMEOUT)) {
		s3c64xx_start_rx_dma(ourport);
		if (ourport->rx_mode == S3C24XX_RX_PIO)
			enable_rx_dma(ourport);
		goto finish;
	}

	if (ourport->rx_mode == S3C24XX_RX_DMA) {
		dmaengine_pause(dma->rx_chan);
		dmaengine_tx_status(dma->rx_chan, dma->rx_cookie, &state);
		dmaengine_terminate_all(dma->rx_chan);
		received = dma->rx_bytes_requested - state.residue;
		s3c24xx_uart_copy_rx_to_tty(ourport, t, received);

		enable_rx_pio(ourport);
	}

	s3c24xx_serial_rx_drain_fifo(ourport);

	if (tty) {
		tty_flip_buffer_push(t);
		tty_kref_put(tty);
	}

	wr_regl(port, S3C2410_UTRSTAT, S3C2410_UTRSTAT_TIMEOUT);

finish:
	spin_unlock_irqrestore(&port->lock, flags);

	return IRQ_HANDLED;
}