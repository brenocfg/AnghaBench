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
struct tty_struct {int /*<<< orphan*/  legacy_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LOCK_SLAVE ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_set_lock_subclass(struct tty_struct *tty)
{
	lockdep_set_subclass(&tty->legacy_mutex, TTY_LOCK_SLAVE);
}