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
struct tty_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void f81232_break_ctl(struct tty_struct *tty, int break_state)
{
	/* FIXME - Stubbed out for now */

	/*
	 * break_state = -1 to turn on break, and 0 to turn off break
	 * see drivers/char/tty_io.c to see it used.
	 * last_set_data_urb_value NEVER has the break bit set in it.
	 */
}