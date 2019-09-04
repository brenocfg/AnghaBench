#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ktermios {int c_cflag; } ;
struct tty_struct {struct ktermios termios; struct gb_tty* driver_data; } ;
struct gb_tty_line_coding {int parity; int data_bits; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate; } ;
struct gb_tty {int ctrlout; int clocal; TYPE_1__ line_coding; } ;
typedef  int /*<<< orphan*/  newline ;

/* Variables and functions */
 int B0 ; 
 int CBAUD ; 
 int CLOCAL ; 
 int CMSPAR ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int C_BAUD (struct tty_struct*) ; 
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  GB_SERIAL_1_STOP_BITS ; 
 int /*<<< orphan*/  GB_SERIAL_2_STOP_BITS ; 
 int /*<<< orphan*/  GB_SERIAL_AUTO_RTSCTS_EN ; 
 int GB_UART_CTRL_DTR ; 
 int GB_UART_CTRL_RTS ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_1__*,struct gb_tty_line_coding*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct gb_tty_line_coding*,int) ; 
 int /*<<< orphan*/  send_control (struct gb_tty*,int) ; 
 int /*<<< orphan*/  send_line_coding (struct gb_tty*) ; 
 int /*<<< orphan*/  tty_get_baud_rate (struct tty_struct*) ; 

__attribute__((used)) static void gb_tty_set_termios(struct tty_struct *tty,
			       struct ktermios *termios_old)
{
	struct gb_tty *gb_tty = tty->driver_data;
	struct ktermios *termios = &tty->termios;
	struct gb_tty_line_coding newline;
	u8 newctrl = gb_tty->ctrlout;

	newline.rate = cpu_to_le32(tty_get_baud_rate(tty));
	newline.format = termios->c_cflag & CSTOPB ?
				GB_SERIAL_2_STOP_BITS : GB_SERIAL_1_STOP_BITS;
	newline.parity = termios->c_cflag & PARENB ?
				(termios->c_cflag & PARODD ? 1 : 2) +
				(termios->c_cflag & CMSPAR ? 2 : 0) : 0;

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		newline.data_bits = 5;
		break;
	case CS6:
		newline.data_bits = 6;
		break;
	case CS7:
		newline.data_bits = 7;
		break;
	case CS8:
	default:
		newline.data_bits = 8;
		break;
	}

	/* FIXME: needs to clear unsupported bits in the termios */
	gb_tty->clocal = ((termios->c_cflag & CLOCAL) != 0);

	if (C_BAUD(tty) == B0) {
		newline.rate = gb_tty->line_coding.rate;
		newctrl &= ~(GB_UART_CTRL_DTR | GB_UART_CTRL_RTS);
	} else if (termios_old && (termios_old->c_cflag & CBAUD) == B0) {
		newctrl |= (GB_UART_CTRL_DTR | GB_UART_CTRL_RTS);
	}

	if (newctrl != gb_tty->ctrlout) {
		gb_tty->ctrlout = newctrl;
		send_control(gb_tty, newctrl);
	}

	if (C_CRTSCTS(tty) && C_BAUD(tty) != B0)
		newline.flow_control |= GB_SERIAL_AUTO_RTSCTS_EN;
	else
		newline.flow_control &= ~GB_SERIAL_AUTO_RTSCTS_EN;

	if (memcmp(&gb_tty->line_coding, &newline, sizeof(newline))) {
		memcpy(&gb_tty->line_coding, &newline, sizeof(newline));
		send_line_coding(gb_tty);
	}
}