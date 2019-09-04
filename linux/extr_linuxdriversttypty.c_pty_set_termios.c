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
struct TYPE_4__ {int c_cflag; } ;
struct tty_struct {int ctrl_status; TYPE_2__ termios; TYPE_1__* link; int /*<<< orphan*/  ctrl_lock; } ;
struct ktermios {int c_lflag; int c_iflag; char* c_cc; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_wait; scalar_t__ packet; } ;

/* Variables and functions */
 int CREAD ; 
 int CS8 ; 
 int CSIZE ; 
 int EXTPROC ; 
 int IXON ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 int L_EXTPROC (struct tty_struct*) ; 
 int PARENB ; 
 char START_CHAR (struct tty_struct*) ; 
 char STOP_CHAR (struct tty_struct*) ; 
 int TIOCPKT_DOSTOP ; 
 int TIOCPKT_IOCTL ; 
 int TIOCPKT_NOSTOP ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pty_set_termios(struct tty_struct *tty,
					struct ktermios *old_termios)
{
	/* See if packet mode change of state. */
	if (tty->link && tty->link->packet) {
		int extproc = (old_termios->c_lflag & EXTPROC) | L_EXTPROC(tty);
		int old_flow = ((old_termios->c_iflag & IXON) &&
				(old_termios->c_cc[VSTOP] == '\023') &&
				(old_termios->c_cc[VSTART] == '\021'));
		int new_flow = (I_IXON(tty) &&
				STOP_CHAR(tty) == '\023' &&
				START_CHAR(tty) == '\021');
		if ((old_flow != new_flow) || extproc) {
			spin_lock_irq(&tty->ctrl_lock);
			if (old_flow != new_flow) {
				tty->ctrl_status &= ~(TIOCPKT_DOSTOP | TIOCPKT_NOSTOP);
				if (new_flow)
					tty->ctrl_status |= TIOCPKT_DOSTOP;
				else
					tty->ctrl_status |= TIOCPKT_NOSTOP;
			}
			if (extproc)
				tty->ctrl_status |= TIOCPKT_IOCTL;
			spin_unlock_irq(&tty->ctrl_lock);
			wake_up_interruptible(&tty->link->read_wait);
		}
	}

	tty->termios.c_cflag &= ~(CSIZE | PARENB);
	tty->termios.c_cflag |= (CS8 | CREAD);
}