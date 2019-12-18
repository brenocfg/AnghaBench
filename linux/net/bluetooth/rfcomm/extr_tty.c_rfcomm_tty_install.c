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
struct tty_struct {struct rfcomm_dev* driver_data; int /*<<< orphan*/  index; } ;
struct tty_driver {int dummy; } ;
struct rfcomm_dlc {int dummy; } ;
struct rfcomm_dev {int /*<<< orphan*/  port; int /*<<< orphan*/  status; int /*<<< orphan*/  flags; struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RFCOMM_RELEASE_ONHUP ; 
 int /*<<< orphan*/  RFCOMM_TTY_ATTACHED ; 
 int /*<<< orphan*/  RFCOMM_TTY_OWNED ; 
 struct rfcomm_dev* rfcomm_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_tty_cleanup (struct tty_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tty_port_install (int /*<<< orphan*/ *,struct tty_driver*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfcomm_tty_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct rfcomm_dev *dev;
	struct rfcomm_dlc *dlc;
	int err;

	dev = rfcomm_dev_get(tty->index);
	if (!dev)
		return -ENODEV;

	dlc = dev->dlc;

	/* Attach TTY and open DLC */
	rfcomm_dlc_lock(dlc);
	tty->driver_data = dev;
	rfcomm_dlc_unlock(dlc);
	set_bit(RFCOMM_TTY_ATTACHED, &dev->flags);

	/* install the tty_port */
	err = tty_port_install(&dev->port, driver, tty);
	if (err) {
		rfcomm_tty_cleanup(tty);
		return err;
	}

	/* take over the tty_port reference if the port was created with the
	 * flag RFCOMM_RELEASE_ONHUP. This will force the release of the port
	 * when the last process closes the tty. The behaviour is expected by
	 * userspace.
	 */
	if (test_bit(RFCOMM_RELEASE_ONHUP, &dev->flags)) {
		set_bit(RFCOMM_TTY_OWNED, &dev->status);
		tty_port_put(&dev->port);
	}

	return 0;
}