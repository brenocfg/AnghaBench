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
struct tty_struct {struct ipw_tty* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct ipw_tty {int tx_bytes_queued; TYPE_1__ port; } ;

/* Variables and functions */

__attribute__((used)) static int ipw_chars_in_buffer(struct tty_struct *linux_tty)
{
	struct ipw_tty *tty = linux_tty->driver_data;

	if (!tty)
		return 0;

	if (!tty->port.count)
		return 0;

	return tty->tx_bytes_queued;
}