#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int hw_stopped; } ;
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  open_wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  cts; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct fwtty_port {unsigned int mstatus; TYPE_2__ port; int /*<<< orphan*/  emit_breaks; int /*<<< orphan*/  break_last; scalar_t__ loopback; int /*<<< orphan*/  hangup; TYPE_1__ icount; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_CLOCAL (struct tty_struct*) ; 
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 unsigned int MCTRL_MASK ; 
 unsigned int OOB_TX_THROTTLE ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 int UART_LSR_BI ; 
 int /*<<< orphan*/  __fwtty_restart_tx (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fwtty_restart_tx (struct fwtty_port*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwtty_update_port_status(struct fwtty_port *port,
				     unsigned int status)
{
	unsigned int delta;
	struct tty_struct *tty;

	/* simulated LSR/MSR status from remote */
	status &= ~MCTRL_MASK;
	delta = (port->mstatus ^ status) & ~MCTRL_MASK;
	delta &= ~(status & TIOCM_RNG);
	port->mstatus = status;

	if (delta & TIOCM_RNG)
		++port->icount.rng;
	if (delta & TIOCM_DSR)
		++port->icount.dsr;
	if (delta & TIOCM_CAR)
		++port->icount.dcd;
	if (delta & TIOCM_CTS)
		++port->icount.cts;

	fwtty_dbg(port, "status: %x delta: %x\n", status, delta);

	if (delta & TIOCM_CAR) {
		tty = tty_port_tty_get(&port->port);
		if (tty && !C_CLOCAL(tty)) {
			if (status & TIOCM_CAR)
				wake_up_interruptible(&port->port.open_wait);
			else
				schedule_work(&port->hangup);
		}
		tty_kref_put(tty);
	}

	if (delta & TIOCM_CTS) {
		tty = tty_port_tty_get(&port->port);
		if (tty && C_CRTSCTS(tty)) {
			if (tty->hw_stopped) {
				if (status & TIOCM_CTS) {
					tty->hw_stopped = 0;
					if (port->loopback)
						__fwtty_restart_tx(port);
					else
						fwtty_restart_tx(port);
				}
			} else {
				if (~status & TIOCM_CTS)
					tty->hw_stopped = 1;
			}
		}
		tty_kref_put(tty);

	} else if (delta & OOB_TX_THROTTLE) {
		tty = tty_port_tty_get(&port->port);
		if (tty) {
			if (tty->hw_stopped) {
				if (~status & OOB_TX_THROTTLE) {
					tty->hw_stopped = 0;
					if (port->loopback)
						__fwtty_restart_tx(port);
					else
						fwtty_restart_tx(port);
				}
			} else {
				if (status & OOB_TX_THROTTLE)
					tty->hw_stopped = 1;
			}
		}
		tty_kref_put(tty);
	}

	if (delta & (UART_LSR_BI << 24)) {
		if (status & (UART_LSR_BI << 24)) {
			port->break_last = jiffies;
			schedule_delayed_work(&port->emit_breaks, 0);
		} else {
			/* run emit_breaks one last time (if pending) */
			mod_delayed_work(system_wq, &port->emit_breaks, 0);
		}
	}

	if (delta & (TIOCM_DSR | TIOCM_CAR | TIOCM_CTS | TIOCM_RNG))
		wake_up_interruptible(&port->port.delta_msr_wait);
}