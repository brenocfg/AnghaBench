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
struct tty_struct {size_t index; int /*<<< orphan*/  count; } ;
struct tty_driver {struct tty_struct** ttys; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_driver_kref_get (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_init_termios (struct tty_struct*) ; 

int tty_standard_install(struct tty_driver *driver, struct tty_struct *tty)
{
	tty_init_termios(tty);
	tty_driver_kref_get(driver);
	tty->count++;
	driver->ttys[tty->index] = tty;
	return 0;
}