#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct TYPE_7__ {TYPE_2__ icount; TYPE_1__* state; scalar_t__ x_char; } ;
struct uart_pmac_port {TYPE_3__ port; int /*<<< orphan*/  flags; int /*<<< orphan*/  curregs; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMACZILOG_FLAG_REGS_HELD ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_TX_ACTIVE ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_TX_STOPPED ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  RES_Tx_P ; 
 unsigned char Tx_BUF_EMP ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ ZS_IS_CONS (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  ZS_IS_OPEN (struct uart_pmac_port*) ; 
 scalar_t__ ZS_REGS_HELD (struct uart_pmac_port*) ; 
 scalar_t__ ZS_TX_STOPPED (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_load_zsregs (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 unsigned char read_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  write_zsdata (struct uart_pmac_port*,scalar_t__) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_transmit_chars(struct uart_pmac_port *uap)
{
	struct circ_buf *xmit;

	if (ZS_IS_CONS(uap)) {
		unsigned char status = read_zsreg(uap, R0);

		/* TX still busy?  Just wait for the next TX done interrupt.
		 *
		 * It can occur because of how we do serial console writes.  It would
		 * be nice to transmit console writes just like we normally would for
		 * a TTY line. (ie. buffered and TX interrupt driven).  That is not
		 * easy because console writes cannot sleep.  One solution might be
		 * to poll on enough port->xmit space becoming free.  -DaveM
		 */
		if (!(status & Tx_BUF_EMP))
			return;
	}

	uap->flags &= ~PMACZILOG_FLAG_TX_ACTIVE;

	if (ZS_REGS_HELD(uap)) {
		pmz_load_zsregs(uap, uap->curregs);
		uap->flags &= ~PMACZILOG_FLAG_REGS_HELD;
	}

	if (ZS_TX_STOPPED(uap)) {
		uap->flags &= ~PMACZILOG_FLAG_TX_STOPPED;
		goto ack_tx_int;
	}

	/* Under some circumstances, we see interrupts reported for
	 * a closed channel. The interrupt mask in R1 is clear, but
	 * R3 still signals the interrupts and we see them when taking
	 * an interrupt for the other channel (this could be a qemu
	 * bug but since the ESCC doc doesn't specify precsiely whether
	 * R3 interrup status bits are masked by R1 interrupt enable
	 * bits, better safe than sorry). --BenH.
	 */
	if (!ZS_IS_OPEN(uap))
		goto ack_tx_int;

	if (uap->port.x_char) {
		uap->flags |= PMACZILOG_FLAG_TX_ACTIVE;
		write_zsdata(uap, uap->port.x_char);
		zssync(uap);
		uap->port.icount.tx++;
		uap->port.x_char = 0;
		return;
	}

	if (uap->port.state == NULL)
		goto ack_tx_int;
	xmit = &uap->port.state->xmit;
	if (uart_circ_empty(xmit)) {
		uart_write_wakeup(&uap->port);
		goto ack_tx_int;
	}
	if (uart_tx_stopped(&uap->port))
		goto ack_tx_int;

	uap->flags |= PMACZILOG_FLAG_TX_ACTIVE;
	write_zsdata(uap, xmit->buf[xmit->tail]);
	zssync(uap);

	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	uap->port.icount.tx++;

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&uap->port);

	return;

ack_tx_int:
	write_zsreg(uap, R0, RES_Tx_P);
	zssync(uap);
}