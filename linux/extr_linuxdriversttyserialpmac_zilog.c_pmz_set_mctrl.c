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
struct uart_pmac_port {unsigned char* curregs; } ;

/* Variables and functions */
 unsigned char DTR ; 
 size_t R5 ; 
 unsigned char RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ ZS_IS_CONS (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_INTMODEM (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_IRDA (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_OPEN (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_debug (char*,unsigned char,unsigned char,unsigned char) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,unsigned char) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned char set_bits, clear_bits;

        /* Do nothing for irda for now... */
	if (ZS_IS_IRDA(uap))
		return;
	/* We get called during boot with a port not up yet */
	if (!(ZS_IS_OPEN(uap) || ZS_IS_CONS(uap)))
		return;

	set_bits = clear_bits = 0;

	if (ZS_IS_INTMODEM(uap)) {
		if (mctrl & TIOCM_RTS)
			set_bits |= RTS;
		else
			clear_bits |= RTS;
	}
	if (mctrl & TIOCM_DTR)
		set_bits |= DTR;
	else
		clear_bits |= DTR;

	/* NOTE: Not subject to 'transmitter active' rule.  */ 
	uap->curregs[R5] |= set_bits;
	uap->curregs[R5] &= ~clear_bits;

	write_zsreg(uap, R5, uap->curregs[R5]);
	pmz_debug("pmz_set_mctrl: set bits: %x, clear bits: %x -> %x\n",
		  set_bits, clear_bits, uap->curregs[R5]);
	zssync(uap);
}