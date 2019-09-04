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
struct tty_struct {scalar_t__ magic; int /*<<< orphan*/  legacy_mutex; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ TTY_MAGIC ; 
 scalar_t__ WARN (int,char*,struct tty_struct*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 

int tty_lock_interruptible(struct tty_struct *tty)
{
	int ret;

	if (WARN(tty->magic != TTY_MAGIC, "L Bad %p\n", tty))
		return -EIO;
	tty_kref_get(tty);
	ret = mutex_lock_interruptible(&tty->legacy_mutex);
	if (ret)
		tty_kref_put(tty);
	return ret;
}