#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  flags; TYPE_2__* link; TYPE_1__* driver; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int count; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ subtype; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ PTY_TYPE_SLAVE ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  TTY_OTHER_CLOSED ; 
 int /*<<< orphan*/  TTY_PTY_LOCK ; 
 int /*<<< orphan*/  TTY_THROTTLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pty_open(struct tty_struct *tty, struct file *filp)
{
	if (!tty || !tty->link)
		return -ENODEV;

	if (test_bit(TTY_OTHER_CLOSED, &tty->flags))
		goto out;
	if (test_bit(TTY_PTY_LOCK, &tty->link->flags))
		goto out;
	if (tty->driver->subtype == PTY_TYPE_SLAVE && tty->link->count != 1)
		goto out;

	clear_bit(TTY_IO_ERROR, &tty->flags);
	clear_bit(TTY_OTHER_CLOSED, &tty->link->flags);
	set_bit(TTY_THROTTLED, &tty->flags);
	return 0;

out:
	set_bit(TTY_IO_ERROR, &tty->flags);
	return -EIO;
}