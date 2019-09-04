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
struct TYPE_2__ {int /*<<< orphan*/  c_lflag; } ;
struct tty_struct {struct acm* driver_data; TYPE_1__ termios; int /*<<< orphan*/  index; } ;
struct tty_driver {int dummy; } ;
struct acm {int quirks; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int DISABLE_ECHO ; 
 int /*<<< orphan*/  ECHO ; 
 int ENODEV ; 
 struct acm* acm_get_by_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int acm_tty_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct acm *acm;
	int retval;

	acm = acm_get_by_minor(tty->index);
	if (!acm)
		return -ENODEV;

	retval = tty_standard_install(driver, tty);
	if (retval)
		goto error_init_termios;

	/*
	 * Suppress initial echoing for some devices which might send data
	 * immediately after acm driver has been installed.
	 */
	if (acm->quirks & DISABLE_ECHO)
		tty->termios.c_lflag &= ~ECHO;

	tty->driver_data = acm;

	return 0;

error_init_termios:
	tty_port_put(&acm->port);
	return retval;
}