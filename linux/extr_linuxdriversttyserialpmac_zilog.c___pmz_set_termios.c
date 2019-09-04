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
struct uart_pmac_port {int* curregs; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; int /*<<< orphan*/  termios_cache; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int CTSIE ; 
 int DCDIE ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_MODEM_STATUS ; 
 size_t R15 ; 
 int SYNCIE ; 
 scalar_t__ UART_ENABLE_MS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ZS_IS_IRDA (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ktermios*,int) ; 
 int /*<<< orphan*/  pmz_convert_to_zs (struct uart_pmac_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pmz_debug (char*,...) ; 
 int /*<<< orphan*/  pmz_irda_setup (struct uart_pmac_port*,unsigned long*) ; 
 int /*<<< orphan*/  pmz_load_zsregs (struct uart_pmac_port*,int*) ; 
 int /*<<< orphan*/  pmz_maybe_update_regs (struct uart_pmac_port*) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 unsigned long uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void __pmz_set_termios(struct uart_port *port, struct ktermios *termios,
			      struct ktermios *old)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned long baud;

	pmz_debug("pmz: set_termios()\n");

	memcpy(&uap->termios_cache, termios, sizeof(struct ktermios));

	/* XXX Check which revs of machines actually allow 1 and 4Mb speeds
	 * on the IR dongle. Note that the IRTTY driver currently doesn't know
	 * about the FIR mode and high speed modes. So these are unused. For
	 * implementing proper support for these, we should probably add some
	 * DMA as well, at least on the Rx side, which isn't a simple thing
	 * at this point.
	 */
	if (ZS_IS_IRDA(uap)) {
		/* Calc baud rate */
		baud = uart_get_baud_rate(port, termios, old, 1200, 4000000);
		pmz_debug("pmz: switch IRDA to %ld bauds\n", baud);
		/* Cet the irda codec to the right rate */
		pmz_irda_setup(uap, &baud);
		/* Set final baud rate */
		pmz_convert_to_zs(uap, termios->c_cflag, termios->c_iflag, baud);
		pmz_load_zsregs(uap, uap->curregs);
		zssync(uap);
	} else {
		baud = uart_get_baud_rate(port, termios, old, 1200, 230400);
		pmz_convert_to_zs(uap, termios->c_cflag, termios->c_iflag, baud);
		/* Make sure modem status interrupts are correctly configured */
		if (UART_ENABLE_MS(&uap->port, termios->c_cflag)) {
			uap->curregs[R15] |= DCDIE | SYNCIE | CTSIE;
			uap->flags |= PMACZILOG_FLAG_MODEM_STATUS;
		} else {
			uap->curregs[R15] &= ~(DCDIE | SYNCIE | CTSIE);
			uap->flags &= ~PMACZILOG_FLAG_MODEM_STATUS;
		}

		/* Load registers to the chip */
		pmz_maybe_update_regs(uap);
	}
	uart_update_timeout(port, termios->c_cflag, baud);

	pmz_debug("pmz: set_termios() done.\n");
}