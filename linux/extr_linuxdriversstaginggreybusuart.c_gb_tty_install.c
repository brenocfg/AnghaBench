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
struct tty_struct {struct gb_tty* driver_data; int /*<<< orphan*/  index; } ;
struct tty_driver {int dummy; } ;
struct gb_tty {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENODEV ; 
 struct gb_tty* get_gb_by_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int gb_tty_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct gb_tty *gb_tty;
	int retval;

	gb_tty = get_gb_by_minor(tty->index);
	if (!gb_tty)
		return -ENODEV;

	retval = tty_standard_install(driver, tty);
	if (retval)
		goto error;

	tty->driver_data = gb_tty;
	return 0;
error:
	tty_port_put(&gb_tty->port);
	return retval;
}