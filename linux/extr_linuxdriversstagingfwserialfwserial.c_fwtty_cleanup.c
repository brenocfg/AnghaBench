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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct fwtty_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwtty_port_put (struct fwtty_port*) ; 

__attribute__((used)) static void fwtty_cleanup(struct tty_struct *tty)
{
	struct fwtty_port *port = tty->driver_data;

	tty->driver_data = NULL;
	fwtty_port_put(port);
}