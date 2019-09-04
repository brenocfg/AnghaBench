#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct mgsl_icount {int /*<<< orphan*/  rxidle; int /*<<< orphan*/  exithunt; int /*<<< orphan*/  brk; } ;
struct TYPE_11__ {int flags; struct tty_struct* tty; } ;
struct TYPE_9__ {scalar_t__ mode; } ;
struct TYPE_10__ {unsigned char ie1_value; unsigned char ie2_value; unsigned char ignore_status_mask1; unsigned char read_status_mask1; int serial_signals; int /*<<< orphan*/  event_wait_q; struct mgsl_icount icount; TYPE_4__ port; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 int ASYNC_SAK ; 
 unsigned char BRKD ; 
 unsigned char CDCD ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 unsigned char FLGD ; 
 unsigned char IDLD ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int MISCSTATUS_DCD_LATCHED ; 
 unsigned char OVRN ; 
 int /*<<< orphan*/  SR1 ; 
 int /*<<< orphan*/  SR2 ; 
 int SerialSignal_DCD ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  do_SAK (struct tty_struct*) ; 
 int /*<<< orphan*/  get_signals (TYPE_2__*) ; 
 int /*<<< orphan*/  isr_io_pin (TYPE_2__*,int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 unsigned char read_reg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_char (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void isr_rxint(SLMP_INFO * info)
{
 	struct tty_struct *tty = info->port.tty;
 	struct	mgsl_icount *icount = &info->icount;
	unsigned char status = read_reg(info, SR1) & info->ie1_value & (FLGD + IDLD + CDCD + BRKD);
	unsigned char status2 = read_reg(info, SR2) & info->ie2_value & OVRN;

	/* clear status bits */
	if (status)
		write_reg(info, SR1, status);

	if (status2)
		write_reg(info, SR2, status2);
	
	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_rxint status=%02X %02x\n",
			__FILE__,__LINE__,info->device_name,status,status2);

	if (info->params.mode == MGSL_MODE_ASYNC) {
		if (status & BRKD) {
			icount->brk++;

			/* process break detection if tty control
			 * is not set to ignore it
			 */
			if (!(status & info->ignore_status_mask1)) {
				if (info->read_status_mask1 & BRKD) {
					tty_insert_flip_char(&info->port, 0, TTY_BREAK);
					if (tty && (info->port.flags & ASYNC_SAK))
						do_SAK(tty);
				}
			}
		}
	}
	else {
		if (status & (FLGD|IDLD)) {
			if (status & FLGD)
				info->icount.exithunt++;
			else if (status & IDLD)
				info->icount.rxidle++;
			wake_up_interruptible(&info->event_wait_q);
		}
	}

	if (status & CDCD) {
		/* simulate a common modem status change interrupt
		 * for our handler
		 */
		get_signals( info );
		isr_io_pin(info,
			MISCSTATUS_DCD_LATCHED|(info->serial_signals&SerialSignal_DCD));
	}
}