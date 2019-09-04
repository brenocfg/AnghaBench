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
struct tty_struct {struct fwtty_port* driver_data; int /*<<< orphan*/  index; } ;
struct tty_driver {int dummy; } ;
struct fwtty_port {int dummy; } ;

/* Variables and functions */
 struct fwtty_port* fwtty_port_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtty_port_put (struct fwtty_port*) ; 
 int /*<<< orphan*/  table_idx (int /*<<< orphan*/ ) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int fwloop_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct fwtty_port *port = fwtty_port_get(table_idx(tty->index));
	int err;

	err = tty_standard_install(driver, tty);
	if (!err)
		tty->driver_data = port;
	else
		fwtty_port_put(port);
	return err;
}