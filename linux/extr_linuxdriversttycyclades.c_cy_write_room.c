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
struct cyclades_port {int xmit_cnt; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cy_write_room(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;
	int ret;

#ifdef CY_DEBUG_IO
	printk(KERN_DEBUG "cyc:cy_write_room ttyC%d\n", info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_write_room"))
		return 0;
	ret = SERIAL_XMIT_SIZE - info->xmit_cnt - 1;
	if (ret < 0)
		ret = 0;
	return ret;
}