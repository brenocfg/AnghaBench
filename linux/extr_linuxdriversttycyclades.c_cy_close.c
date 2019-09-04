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
struct file {int dummy; } ;
struct cyclades_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tty_port_close (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static void cy_close(struct tty_struct *tty, struct file *filp)
{
	struct cyclades_port *info = tty->driver_data;
	if (!info || serial_paranoia_check(info, tty->name, "cy_close"))
		return;
	tty_port_close(&info->port, tty, filp);
}