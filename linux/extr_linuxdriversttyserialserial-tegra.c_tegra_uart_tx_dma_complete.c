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
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* state; } ;
struct tegra_uart_port {unsigned int tx_bytes_requested; TYPE_2__ uport; scalar_t__ tx_in_progress; int /*<<< orphan*/  tx_dma_desc; int /*<<< orphan*/  tx_cookie; int /*<<< orphan*/  tx_dma_chan; } ;
struct dma_tx_state {unsigned int residue; } ;
struct circ_buf {unsigned int tail; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_uart_start_next_tx (struct tegra_uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_2__*) ; 

__attribute__((used)) static void tegra_uart_tx_dma_complete(void *args)
{
	struct tegra_uart_port *tup = args;
	struct circ_buf *xmit = &tup->uport.state->xmit;
	struct dma_tx_state state;
	unsigned long flags;
	unsigned int count;

	dmaengine_tx_status(tup->tx_dma_chan, tup->tx_cookie, &state);
	count = tup->tx_bytes_requested - state.residue;
	async_tx_ack(tup->tx_dma_desc);
	spin_lock_irqsave(&tup->uport.lock, flags);
	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	tup->tx_in_progress = 0;
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&tup->uport);
	tegra_uart_start_next_tx(tup);
	spin_unlock_irqrestore(&tup->uport.lock, flags);
}