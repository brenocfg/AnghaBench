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
struct tty_struct {int receive_room; int /*<<< orphan*/ * disc_data; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 

__attribute__((used)) static int nci_uart_tty_open(struct tty_struct *tty)
{
	/* Error if the tty has no write op instead of leaving an exploitable
	 * hole
	 */
	if (!tty->ops->write)
		return -EOPNOTSUPP;

	tty->disc_data = NULL;
	tty->receive_room = 65536;

	/* Flush any pending characters in the driver */
	tty_driver_flush_buffer(tty);

	return 0;
}