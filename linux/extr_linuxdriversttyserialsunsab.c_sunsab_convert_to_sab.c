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
struct TYPE_2__ {int read_status_mask; int ignore_status_mask; int uartclk; } ;
struct uart_sunsab_port {unsigned char cached_dafo; int cached_ebrg; int tec_timeout; int cec_timeout; int /*<<< orphan*/  irqflags; int /*<<< orphan*/  cached_mode; TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int BRKINT ; 
 unsigned int CREAD ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int IGNBRK ; 
 unsigned int IGNPAR ; 
 unsigned int INPCK ; 
 unsigned int PARENB ; 
 unsigned int PARMRK ; 
 unsigned int PARODD ; 
 unsigned char SAB82532_DAFO_CHL5 ; 
 unsigned char SAB82532_DAFO_CHL6 ; 
 unsigned char SAB82532_DAFO_CHL7 ; 
 unsigned char SAB82532_DAFO_CHL8 ; 
 unsigned char SAB82532_DAFO_PARE ; 
 unsigned char SAB82532_DAFO_PAR_EVEN ; 
 unsigned char SAB82532_DAFO_PAR_ODD ; 
 unsigned char SAB82532_DAFO_STOP ; 
 int SAB82532_ISR0_CDSC ; 
 int SAB82532_ISR0_FERR ; 
 int SAB82532_ISR0_PERR ; 
 int SAB82532_ISR0_RFO ; 
 int SAB82532_ISR0_RPF ; 
 int SAB82532_ISR0_TCD ; 
 int SAB82532_ISR0_TIME ; 
 int SAB82532_ISR1_ALLS ; 
 int SAB82532_ISR1_BRK ; 
 int SAB82532_ISR1_CSC ; 
 int SAB82532_ISR1_XPR ; 
 int /*<<< orphan*/  SAB82532_MODE_RAC ; 
 int /*<<< orphan*/  SAB82532_REGS_PENDING ; 
 int /*<<< orphan*/  SAB82532_XPR ; 
 int /*<<< orphan*/  calc_ebrg (unsigned int,int*,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunsab_tx_idle (struct uart_sunsab_port*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_update_timeout (TYPE_1__*,unsigned int,int) ; 

__attribute__((used)) static void sunsab_convert_to_sab(struct uart_sunsab_port *up, unsigned int cflag,
				  unsigned int iflag, unsigned int baud,
				  unsigned int quot)
{
	unsigned char dafo;
	int bits, n, m;

	/* Byte size and parity */
	switch (cflag & CSIZE) {
	      case CS5: dafo = SAB82532_DAFO_CHL5; bits = 7; break;
	      case CS6: dafo = SAB82532_DAFO_CHL6; bits = 8; break;
	      case CS7: dafo = SAB82532_DAFO_CHL7; bits = 9; break;
	      case CS8: dafo = SAB82532_DAFO_CHL8; bits = 10; break;
	      /* Never happens, but GCC is too dumb to figure it out */
	      default:  dafo = SAB82532_DAFO_CHL5; bits = 7; break;
	}

	if (cflag & CSTOPB) {
		dafo |= SAB82532_DAFO_STOP;
		bits++;
	}

	if (cflag & PARENB) {
		dafo |= SAB82532_DAFO_PARE;
		bits++;
	}

	if (cflag & PARODD) {
		dafo |= SAB82532_DAFO_PAR_ODD;
	} else {
		dafo |= SAB82532_DAFO_PAR_EVEN;
	}
	up->cached_dafo = dafo;

	calc_ebrg(baud, &n, &m);

	up->cached_ebrg = n | (m << 6);

	up->tec_timeout = (10 * 1000000) / baud;
	up->cec_timeout = up->tec_timeout >> 2;

	/* CTS flow control flags */
	/* We encode read_status_mask and ignore_status_mask like so:
	 *
	 * ---------------------
	 * | ... | ISR1 | ISR0 |
	 * ---------------------
	 *  ..    15   8 7    0
	 */

	up->port.read_status_mask = (SAB82532_ISR0_TCD | SAB82532_ISR0_TIME |
				     SAB82532_ISR0_RFO | SAB82532_ISR0_RPF |
				     SAB82532_ISR0_CDSC);
	up->port.read_status_mask |= (SAB82532_ISR1_CSC |
				      SAB82532_ISR1_ALLS |
				      SAB82532_ISR1_XPR) << 8;
	if (iflag & INPCK)
		up->port.read_status_mask |= (SAB82532_ISR0_PERR |
					      SAB82532_ISR0_FERR);
	if (iflag & (IGNBRK | BRKINT | PARMRK))
		up->port.read_status_mask |= (SAB82532_ISR1_BRK << 8);

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	if (iflag & IGNPAR)
		up->port.ignore_status_mask |= (SAB82532_ISR0_PERR |
						SAB82532_ISR0_FERR);
	if (iflag & IGNBRK) {
		up->port.ignore_status_mask |= (SAB82532_ISR1_BRK << 8);
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (iflag & IGNPAR)
			up->port.ignore_status_mask |= SAB82532_ISR0_RFO;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((cflag & CREAD) == 0)
		up->port.ignore_status_mask |= (SAB82532_ISR0_RPF |
						SAB82532_ISR0_TCD);

	uart_update_timeout(&up->port, cflag,
			    (up->port.uartclk / (16 * quot)));

	/* Now schedule a register update when the chip's
	 * transmitter is idle.
	 */
	up->cached_mode |= SAB82532_MODE_RAC;
	set_bit(SAB82532_REGS_PENDING, &up->irqflags);
	if (test_bit(SAB82532_XPR, &up->irqflags))
		sunsab_tx_idle(up);
}