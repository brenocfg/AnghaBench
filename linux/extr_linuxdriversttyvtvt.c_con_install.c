#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct tty_struct* tty; } ;
struct vc_data {scalar_t__ vc_utf; int /*<<< orphan*/  vc_cols; int /*<<< orphan*/  vc_rows; TYPE_4__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  c_iflag; } ;
struct TYPE_5__ {int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; } ;
struct tty_struct {unsigned int index; TYPE_2__ termios; TYPE_1__ winsize; struct vc_data* driver_data; } ;
struct tty_driver {int dummy; } ;
struct TYPE_7__ {struct vc_data* d; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  IUTF8 ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int tty_port_install (TYPE_4__*,struct tty_driver*,struct tty_struct*) ; 
 int vc_allocate (unsigned int) ; 
 TYPE_3__* vc_cons ; 

__attribute__((used)) static int con_install(struct tty_driver *driver, struct tty_struct *tty)
{
	unsigned int currcons = tty->index;
	struct vc_data *vc;
	int ret;

	console_lock();
	ret = vc_allocate(currcons);
	if (ret)
		goto unlock;

	vc = vc_cons[currcons].d;

	/* Still being freed */
	if (vc->port.tty) {
		ret = -ERESTARTSYS;
		goto unlock;
	}

	ret = tty_port_install(&vc->port, driver, tty);
	if (ret)
		goto unlock;

	tty->driver_data = vc;
	vc->port.tty = tty;

	if (!tty->winsize.ws_row && !tty->winsize.ws_col) {
		tty->winsize.ws_row = vc_cons[currcons].d->vc_rows;
		tty->winsize.ws_col = vc_cons[currcons].d->vc_cols;
	}
	if (vc->vc_utf)
		tty->termios.c_iflag |= IUTF8;
	else
		tty->termios.c_iflag &= ~IUTF8;
unlock:
	console_unlock();
	return ret;
}