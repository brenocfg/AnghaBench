#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  write_wait; int /*<<< orphan*/  flags; } ;
struct tty_port {struct serdev_controller* client_data; } ;
struct serport {int /*<<< orphan*/  flags; } ;
struct serdev_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 struct serport* serdev_controller_get_drvdata (struct serdev_controller*) ; 
 int /*<<< orphan*/  serdev_controller_write_wakeup (struct serdev_controller*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttyport_write_wakeup(struct tty_port *port)
{
	struct serdev_controller *ctrl = port->client_data;
	struct serport *serport = serdev_controller_get_drvdata(ctrl);
	struct tty_struct *tty;

	tty = tty_port_tty_get(port);
	if (!tty)
		return;

	if (test_and_clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags) &&
	    test_bit(SERPORT_ACTIVE, &serport->flags))
		serdev_controller_write_wakeup(ctrl);

	/* Wake up any tty_wait_until_sent() */
	wake_up_interruptible(&tty->write_wait);

	tty_kref_put(tty);
}