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
struct tty_struct {scalar_t__ stopped; } ;

/* Variables and functions */

__attribute__((used)) static int con_write_room(struct tty_struct *tty)
{
	if (tty->stopped)
		return 0;
	return 32768;		/* No limit, really; we're not buffering */
}