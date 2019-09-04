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
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct cyclades_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  cy_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  cy_shutdown (struct cyclades_port*,struct tty_struct*) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cy_hangup(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;

#ifdef CY_DEBUG_OTHER
	printk(KERN_DEBUG "cyc:cy_hangup ttyC%d\n", info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_hangup"))
		return;

	cy_flush_buffer(tty);
	cy_shutdown(info, tty);
	tty_port_hangup(&info->port);
}