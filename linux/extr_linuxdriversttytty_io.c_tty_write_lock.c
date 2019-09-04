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
struct tty_struct {int /*<<< orphan*/  atomic_write_lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_write_lock(struct tty_struct *tty, int ndelay)
{
	if (!mutex_trylock(&tty->atomic_write_lock)) {
		if (ndelay)
			return -EAGAIN;
		if (mutex_lock_interruptible(&tty->atomic_write_lock))
			return -ERESTARTSYS;
	}
	return 0;
}