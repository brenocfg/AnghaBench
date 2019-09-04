#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; TYPE_1__* driver_data; int /*<<< orphan*/  name; } ;
struct tty_driver {int dummy; } ;
struct TYPE_4__ {int line; int /*<<< orphan*/  port; scalar_t__ init_error; int /*<<< orphan*/  device_name; struct TYPE_4__* next_device; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  printk (char*,char*,int,int,...) ; 
 scalar_t__ sanity_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int synclinkmp_device_count ; 
 TYPE_1__* synclinkmp_device_list ; 
 int tty_port_install (int /*<<< orphan*/ *,struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int install(struct tty_driver *driver, struct tty_struct *tty)
{
	SLMP_INFO *info;
	int line = tty->index;

	if (line >= synclinkmp_device_count) {
		printk("%s(%d): open with invalid line #%d.\n",
			__FILE__,__LINE__,line);
		return -ENODEV;
	}

	info = synclinkmp_device_list;
	while (info && info->line != line)
		info = info->next_device;
	if (sanity_check(info, tty->name, "open"))
		return -ENODEV;
	if (info->init_error) {
		printk("%s(%d):%s device is not allocated, init error=%d\n",
			__FILE__, __LINE__, info->device_name,
			info->init_error);
		return -ENODEV;
	}

	tty->driver_data = info;

	return tty_port_install(&info->port, driver, tty);
}