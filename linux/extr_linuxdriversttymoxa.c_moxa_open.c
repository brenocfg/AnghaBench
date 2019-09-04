#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; int /*<<< orphan*/  termios; struct moxa_port* driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;
struct moxa_port {scalar_t__ type; TYPE_1__ port; scalar_t__ statusflags; } ;
struct moxa_board_conf {int numPorts; struct moxa_port* ports; int /*<<< orphan*/  ready; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENODEV ; 
 int EPERM ; 
 int ERESTARTSYS ; 
 int MAX_PORTS ; 
 int MAX_PORTS_PER_BOARD ; 
 int /*<<< orphan*/  MoxaPortEnable (struct moxa_port*) ; 
 int /*<<< orphan*/  MoxaPortLineCtrl (struct moxa_port*,int,int) ; 
 int /*<<< orphan*/  MoxaSetFifo (struct moxa_port*,int) ; 
 scalar_t__ PORT_16550A ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct moxa_board_conf* moxa_boards ; 
 int /*<<< orphan*/  moxa_openlock ; 
 int /*<<< orphan*/  moxa_set_tty_param (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tty_port_block_til_ready (TYPE_1__*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,struct tty_struct*) ; 

__attribute__((used)) static int moxa_open(struct tty_struct *tty, struct file *filp)
{
	struct moxa_board_conf *brd;
	struct moxa_port *ch;
	int port;

	port = tty->index;
	if (port == MAX_PORTS) {
		return capable(CAP_SYS_ADMIN) ? 0 : -EPERM;
	}
	if (mutex_lock_interruptible(&moxa_openlock))
		return -ERESTARTSYS;
	brd = &moxa_boards[port / MAX_PORTS_PER_BOARD];
	if (!brd->ready) {
		mutex_unlock(&moxa_openlock);
		return -ENODEV;
	}

	if (port % MAX_PORTS_PER_BOARD >= brd->numPorts) {
		mutex_unlock(&moxa_openlock);
		return -ENODEV;
	}

	ch = &brd->ports[port % MAX_PORTS_PER_BOARD];
	ch->port.count++;
	tty->driver_data = ch;
	tty_port_tty_set(&ch->port, tty);
	mutex_lock(&ch->port.mutex);
	if (!tty_port_initialized(&ch->port)) {
		ch->statusflags = 0;
		moxa_set_tty_param(tty, &tty->termios);
		MoxaPortLineCtrl(ch, 1, 1);
		MoxaPortEnable(ch);
		MoxaSetFifo(ch, ch->type == PORT_16550A);
		tty_port_set_initialized(&ch->port, 1);
	}
	mutex_unlock(&ch->port.mutex);
	mutex_unlock(&moxa_openlock);

	return tty_port_block_til_ready(&ch->port, tty, filp);
}