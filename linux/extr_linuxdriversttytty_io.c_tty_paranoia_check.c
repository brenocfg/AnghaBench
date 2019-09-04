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
struct inode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int tty_paranoia_check(struct tty_struct *tty, struct inode *inode,
			      const char *routine)
{
#ifdef TTY_PARANOIA_CHECK
	if (!tty) {
		pr_warn("(%d:%d): %s: NULL tty\n",
			imajor(inode), iminor(inode), routine);
		return 1;
	}
	if (tty->magic != TTY_MAGIC) {
		pr_warn("(%d:%d): %s: bad magic number\n",
			imajor(inode), iminor(inode), routine);
		return 1;
	}
#endif
	return 0;
}