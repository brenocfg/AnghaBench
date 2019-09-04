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
struct vc_data {int dummy; } ;
struct tty_struct {struct vc_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  set_cursor (struct vc_data*) ; 

__attribute__((used)) static void con_flush_chars(struct tty_struct *tty)
{
	struct vc_data *vc;

	if (in_interrupt())	/* from flush_to_ldisc */
		return;

	/* if we race with con_close(), vt may be null */
	console_lock();
	vc = tty->driver_data;
	if (vc)
		set_cursor(vc);
	console_unlock();
}