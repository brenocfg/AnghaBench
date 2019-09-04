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
struct tty_struct {int index; struct mgsl_struct* driver_data; int /*<<< orphan*/  name; } ;
struct tty_driver {int dummy; } ;
struct mgsl_struct {int line; int /*<<< orphan*/  port; struct mgsl_struct* next_device; } ;

/* Variables and functions */
 int ENODEV ; 
 int mgsl_device_count ; 
 struct mgsl_struct* mgsl_device_list ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 
 int tty_port_install (int /*<<< orphan*/ *,struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int mgsl_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct mgsl_struct *info;
	int line = tty->index;

	/* verify range of specified line number */
	if (line >= mgsl_device_count) {
		printk("%s(%d):mgsl_open with invalid line #%d.\n",
			__FILE__, __LINE__, line);
		return -ENODEV;
	}

	/* find the info structure for the specified line */
	info = mgsl_device_list;
	while (info && info->line != line)
		info = info->next_device;
	if (mgsl_paranoia_check(info, tty->name, "mgsl_open"))
		return -ENODEV;
	tty->driver_data = info;

	return tty_port_install(&info->port, driver, tty);
}