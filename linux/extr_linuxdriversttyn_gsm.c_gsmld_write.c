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
struct tty_struct {int /*<<< orphan*/  flags; TYPE_1__* ops; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct tty_struct*,unsigned char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,unsigned char const*,size_t) ; 
 int tty_write_room (struct tty_struct*) ; 

__attribute__((used)) static ssize_t gsmld_write(struct tty_struct *tty, struct file *file,
			   const unsigned char *buf, size_t nr)
{
	int space = tty_write_room(tty);
	if (space >= nr)
		return tty->ops->write(tty, buf, nr);
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	return -ENOBUFS;
}