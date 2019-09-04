#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  tx; } ;
struct TYPE_8__ {unsigned char x_char; int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct dz_port {TYPE_3__ port; } ;
struct dz_mux {struct dz_port* dport; } ;
struct circ_buf {unsigned char* buf; size_t tail; } ;
struct TYPE_6__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DZ_CSR ; 
 int /*<<< orphan*/  DZ_TDR ; 
 scalar_t__ DZ_WAKEUP_CHARS ; 
 int DZ_XMIT_SIZE ; 
 size_t LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_out (struct dz_port*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dz_stop_tx (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 

__attribute__((used)) static inline void dz_transmit_chars(struct dz_mux *mux)
{
	struct dz_port *dport = &mux->dport[0];
	struct circ_buf *xmit;
	unsigned char tmp;
	u16 status;

	status = dz_in(dport, DZ_CSR);
	dport = &mux->dport[LINE(status)];
	xmit = &dport->port.state->xmit;

	if (dport->port.x_char) {		/* XON/XOFF chars */
		dz_out(dport, DZ_TDR, dport->port.x_char);
		dport->port.icount.tx++;
		dport->port.x_char = 0;
		return;
	}
	/* If nothing to do or stopped or hardware stopped. */
	if (uart_circ_empty(xmit) || uart_tx_stopped(&dport->port)) {
		spin_lock(&dport->port.lock);
		dz_stop_tx(&dport->port);
		spin_unlock(&dport->port.lock);
		return;
	}

	/*
	 * If something to do... (remember the dz has no output fifo,
	 * so we go one char at a time) :-<
	 */
	tmp = xmit->buf[xmit->tail];
	xmit->tail = (xmit->tail + 1) & (DZ_XMIT_SIZE - 1);
	dz_out(dport, DZ_TDR, tmp);
	dport->port.icount.tx++;

	if (uart_circ_chars_pending(xmit) < DZ_WAKEUP_CHARS)
		uart_write_wakeup(&dport->port);

	/* Are we are done. */
	if (uart_circ_empty(xmit)) {
		spin_lock(&dport->port.lock);
		dz_stop_tx(&dport->port);
		spin_unlock(&dport->port.lock);
	}
}