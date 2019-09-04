#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int rx; int /*<<< orphan*/  brk; int /*<<< orphan*/  overrun; } ;
struct uart_port {int read_status_mask; int /*<<< orphan*/  lock; TYPE_2__ icount; int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct msm_dma {int enable_bit; scalar_t__* virt; int /*<<< orphan*/  dir; int /*<<< orphan*/  phys; int /*<<< orphan*/  count; } ;
struct msm_port {int break_detected; struct msm_dma rx_dma; struct uart_port uart; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 int /*<<< orphan*/  UARTDM_DMEN ; 
 int /*<<< orphan*/  UARTDM_RX_SIZE ; 
 int /*<<< orphan*/  UARTDM_RX_TOTAL_SNAP ; 
 int /*<<< orphan*/  UART_CR ; 
 int UART_CR_CMD_RESET_ERR ; 
 int /*<<< orphan*/  UART_SR ; 
 int UART_SR_OVERRUN ; 
 int UART_SR_RX_BREAK ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_start_rx_dma (struct msm_port*) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,scalar_t__,char) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 int uart_handle_sysrq_char (struct uart_port*,scalar_t__) ; 

__attribute__((used)) static void msm_complete_rx_dma(void *args)
{
	struct msm_port *msm_port = args;
	struct uart_port *port = &msm_port->uart;
	struct tty_port *tport = &port->state->port;
	struct msm_dma *dma = &msm_port->rx_dma;
	int count = 0, i, sysrq;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	/* Already stopped */
	if (!dma->count)
		goto done;

	val = msm_read(port, UARTDM_DMEN);
	val &= ~dma->enable_bit;
	msm_write(port, val, UARTDM_DMEN);

	if (msm_read(port, UART_SR) & UART_SR_OVERRUN) {
		port->icount.overrun++;
		tty_insert_flip_char(tport, 0, TTY_OVERRUN);
		msm_write(port, UART_CR_CMD_RESET_ERR, UART_CR);
	}

	count = msm_read(port, UARTDM_RX_TOTAL_SNAP);

	port->icount.rx += count;

	dma->count = 0;

	dma_unmap_single(port->dev, dma->phys, UARTDM_RX_SIZE, dma->dir);

	for (i = 0; i < count; i++) {
		char flag = TTY_NORMAL;

		if (msm_port->break_detected && dma->virt[i] == 0) {
			port->icount.brk++;
			flag = TTY_BREAK;
			msm_port->break_detected = false;
			if (uart_handle_break(port))
				continue;
		}

		if (!(port->read_status_mask & UART_SR_RX_BREAK))
			flag = TTY_NORMAL;

		spin_unlock_irqrestore(&port->lock, flags);
		sysrq = uart_handle_sysrq_char(port, dma->virt[i]);
		spin_lock_irqsave(&port->lock, flags);
		if (!sysrq)
			tty_insert_flip_char(tport, dma->virt[i], flag);
	}

	msm_start_rx_dma(msm_port);
done:
	spin_unlock_irqrestore(&port->lock, flags);

	if (count)
		tty_flip_buffer_push(tport);
}