#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned int c_cflag; } ;
struct TYPE_18__ {TYPE_1__ termios; } ;
struct TYPE_17__ {TYPE_6__* tty; } ;
struct TYPE_15__ {int data_bits; int stop_bits; int data_rate; int /*<<< orphan*/  parity; } ;
struct TYPE_16__ {int serial_signals; int timeout; int read_status_mask2; int ignore_status_mask2; TYPE_4__ port; int /*<<< orphan*/  ignore_status_mask1; int /*<<< orphan*/  read_status_mask1; TYPE_2__ params; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_PARITY_EVEN ; 
 int /*<<< orphan*/  ASYNC_PARITY_NONE ; 
 int /*<<< orphan*/  ASYNC_PARITY_ODD ; 
 int /*<<< orphan*/  BRKD ; 
 unsigned int CBAUD ; 
 unsigned int CLOCAL ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int FRME ; 
 int HZ ; 
 scalar_t__ I_BRKINT (TYPE_6__*) ; 
 scalar_t__ I_IGNBRK (TYPE_6__*) ; 
 scalar_t__ I_IGNPAR (TYPE_6__*) ; 
 scalar_t__ I_INPCK (TYPE_6__*) ; 
 scalar_t__ I_PARMRK (TYPE_6__*) ; 
 int OVRN ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 int PE ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_hw (TYPE_3__*) ; 
 int tty_get_baud_rate (TYPE_6__*) ; 
 int /*<<< orphan*/  tty_port_set_check_carrier (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  tty_port_set_cts_flow (TYPE_4__*,unsigned int) ; 

__attribute__((used)) static void change_params(SLMP_INFO *info)
{
	unsigned cflag;
	int bits_per_char;

	if (!info->port.tty)
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s change_params()\n",
			 __FILE__,__LINE__, info->device_name );

	cflag = info->port.tty->termios.c_cflag;

	/* if B0 rate (hangup) specified then negate RTS and DTR */
	/* otherwise assert RTS and DTR */
 	if (cflag & CBAUD)
		info->serial_signals |= SerialSignal_RTS | SerialSignal_DTR;
	else
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);

	/* byte size and parity */

	switch (cflag & CSIZE) {
	      case CS5: info->params.data_bits = 5; break;
	      case CS6: info->params.data_bits = 6; break;
	      case CS7: info->params.data_bits = 7; break;
	      case CS8: info->params.data_bits = 8; break;
	      /* Never happens, but GCC is too dumb to figure it out */
	      default:  info->params.data_bits = 7; break;
	      }

	if (cflag & CSTOPB)
		info->params.stop_bits = 2;
	else
		info->params.stop_bits = 1;

	info->params.parity = ASYNC_PARITY_NONE;
	if (cflag & PARENB) {
		if (cflag & PARODD)
			info->params.parity = ASYNC_PARITY_ODD;
		else
			info->params.parity = ASYNC_PARITY_EVEN;
#ifdef CMSPAR
		if (cflag & CMSPAR)
			info->params.parity = ASYNC_PARITY_SPACE;
#endif
	}

	/* calculate number of jiffies to transmit a full
	 * FIFO (32 bytes) at specified data rate
	 */
	bits_per_char = info->params.data_bits +
			info->params.stop_bits + 1;

	/* if port data rate is set to 460800 or less then
	 * allow tty settings to override, otherwise keep the
	 * current data rate.
	 */
	if (info->params.data_rate <= 460800) {
		info->params.data_rate = tty_get_baud_rate(info->port.tty);
	}

	if ( info->params.data_rate ) {
		info->timeout = (32*HZ*bits_per_char) /
				info->params.data_rate;
	}
	info->timeout += HZ/50;		/* Add .02 seconds of slop */

	tty_port_set_cts_flow(&info->port, cflag & CRTSCTS);
	tty_port_set_check_carrier(&info->port, ~cflag & CLOCAL);

	/* process tty input control flags */

	info->read_status_mask2 = OVRN;
	if (I_INPCK(info->port.tty))
		info->read_status_mask2 |= PE | FRME;
 	if (I_BRKINT(info->port.tty) || I_PARMRK(info->port.tty))
 		info->read_status_mask1 |= BRKD;
	if (I_IGNPAR(info->port.tty))
		info->ignore_status_mask2 |= PE | FRME;
	if (I_IGNBRK(info->port.tty)) {
		info->ignore_status_mask1 |= BRKD;
		/* If ignoring parity and break indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		if (I_IGNPAR(info->port.tty))
			info->ignore_status_mask2 |= OVRN;
	}

	program_hw(info);
}