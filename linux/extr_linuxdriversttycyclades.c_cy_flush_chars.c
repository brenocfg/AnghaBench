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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  xmit_buf; } ;
struct cyclades_port {scalar_t__ xmit_cnt; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  start_xmit (struct cyclades_port*) ; 

__attribute__((used)) static void cy_flush_chars(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;

#ifdef CY_DEBUG_IO
	printk(KERN_DEBUG "cyc:cy_flush_chars ttyC%d\n", info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_flush_chars"))
		return;

	if (info->xmit_cnt <= 0 || tty->stopped || tty->hw_stopped ||
			!info->port.xmit_buf)
		return;

	start_xmit(info);
}