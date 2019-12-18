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
struct nci_uart {TYPE_1__* tty; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  termios_rwsem; struct ktermios termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTSCTS ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_set_termios (TYPE_1__*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void nci_uart_set_config(struct nci_uart *nu, int baudrate, int flow_ctrl)
{
	struct ktermios new_termios;

	if (!nu->tty)
		return;

	down_read(&nu->tty->termios_rwsem);
	new_termios = nu->tty->termios;
	up_read(&nu->tty->termios_rwsem);
	tty_termios_encode_baud_rate(&new_termios, baudrate, baudrate);

	if (flow_ctrl)
		new_termios.c_cflag |= CRTSCTS;
	else
		new_termios.c_cflag &= ~CRTSCTS;

	tty_set_termios(nu->tty, &new_termios);
}