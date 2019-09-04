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
struct ktermios {int c_iflag; int c_lflag; int c_cflag; int /*<<< orphan*/  c_oflag; } ;
struct tty_struct {TYPE_1__* ops; struct ktermios termios; } ;
struct serport {int /*<<< orphan*/  tty_idx; int /*<<< orphan*/  flags; struct tty_struct* tty; int /*<<< orphan*/  tty_drv; } ;
struct serdev_controller {int dummy; } ;
struct TYPE_2__ {int (* open ) (struct tty_struct*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close ) (struct tty_struct*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int BRKINT ; 
 int CLOCAL ; 
 int CRTSCTS ; 
 int CS8 ; 
 int CSIZE ; 
 int ECHO ; 
 int ECHONL ; 
 int ENODEV ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNCR ; 
 int INLCR ; 
 int ISIG ; 
 int ISTRIP ; 
 scalar_t__ IS_ERR (struct tty_struct*) ; 
 int IXON ; 
 int /*<<< orphan*/  OPOST ; 
 int PARENB ; 
 int PARMRK ; 
 int PTR_ERR (struct tty_struct*) ; 
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*,int /*<<< orphan*/ *) ; 
 struct tty_struct* tty_init_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_release_struct (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_set_termios (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

__attribute__((used)) static int ttyport_open(struct serdev_controller *ctrl)
{
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty;
	struct ktermios ktermios;
	int ret;

	tty = tty_init_dev(serport->tty_drv, serport->tty_idx);
	if (IS_ERR(tty))
		return PTR_ERR(tty);
	serport->tty = tty;

	if (!tty->ops->open || !tty->ops->close) {
		ret = -ENODEV;
		goto err_unlock;
	}

	ret = tty->ops->open(serport->tty, NULL);
	if (ret)
		goto err_close;

	tty_unlock(serport->tty);

	/* Bring the UART into a known 8 bits no parity hw fc state */
	ktermios = tty->termios;
	ktermios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
			      INLCR | IGNCR | ICRNL | IXON);
	ktermios.c_oflag &= ~OPOST;
	ktermios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	ktermios.c_cflag &= ~(CSIZE | PARENB);
	ktermios.c_cflag |= CS8;
	ktermios.c_cflag |= CRTSCTS;
	/* Hangups are not supported so make sure to ignore carrier detect. */
	ktermios.c_cflag |= CLOCAL;
	tty_set_termios(tty, &ktermios);

	set_bit(SERPORT_ACTIVE, &serport->flags);

	return 0;

err_close:
	tty->ops->close(tty, NULL);
err_unlock:
	tty_unlock(tty);
	tty_release_struct(tty, serport->tty_idx);

	return ret;
}