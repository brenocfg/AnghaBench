#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct fwtty_transaction {TYPE_3__ dma_pended; struct fwtty_port* port; } ;
struct TYPE_5__ {int /*<<< orphan*/  dropped; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct fwtty_port {int /*<<< orphan*/  port; TYPE_2__ stats; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_fifo; TYPE_1__ icount; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
#define  RCODE_COMPLETE 128 
 int WAKEUP_CHARS ; 
 int dma_fifo_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fifo_out_complete (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwtty_tx_complete(struct fw_card *card, int rcode,
			      void *data, size_t length,
			      struct fwtty_transaction *txn)
{
	struct fwtty_port *port = txn->port;
	int len;

	fwtty_dbg(port, "rcode: %d\n", rcode);

	switch (rcode) {
	case RCODE_COMPLETE:
		spin_lock_bh(&port->lock);
		dma_fifo_out_complete(&port->tx_fifo, &txn->dma_pended);
		len = dma_fifo_level(&port->tx_fifo);
		spin_unlock_bh(&port->lock);

		port->icount.tx += txn->dma_pended.len;
		break;

	default:
		/* TODO: implement retries */
		spin_lock_bh(&port->lock);
		dma_fifo_out_complete(&port->tx_fifo, &txn->dma_pended);
		len = dma_fifo_level(&port->tx_fifo);
		spin_unlock_bh(&port->lock);

		port->stats.dropped += txn->dma_pended.len;
	}

	if (len < WAKEUP_CHARS)
		tty_port_tty_wakeup(&port->port);
}