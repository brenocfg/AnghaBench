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
struct tty_struct {size_t index; } ;
struct tty_driver {int /*<<< orphan*/ ** ttys; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct tty_driver*,struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static void tty_driver_remove_tty(struct tty_driver *driver, struct tty_struct *tty)
{
	if (driver->ops->remove)
		driver->ops->remove(driver, tty);
	else
		driver->ttys[tty->index] = NULL;
}