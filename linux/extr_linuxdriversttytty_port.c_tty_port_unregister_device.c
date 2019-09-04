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
struct tty_port {int dummy; } ;
struct tty_driver {int dummy; } ;

/* Variables and functions */
 int serdev_tty_port_unregister (struct tty_port*) ; 
 int /*<<< orphan*/  tty_unregister_device (struct tty_driver*,unsigned int) ; 

void tty_port_unregister_device(struct tty_port *port,
		struct tty_driver *driver, unsigned index)
{
	int ret;

	ret = serdev_tty_port_unregister(port);
	if (ret == 0)
		return;

	tty_unregister_device(driver, index);
}