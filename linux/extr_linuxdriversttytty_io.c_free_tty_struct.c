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
struct tty_struct {int magic; struct tty_struct* write_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tty_struct*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_ldisc_deinit (struct tty_struct*) ; 

__attribute__((used)) static void free_tty_struct(struct tty_struct *tty)
{
	tty_ldisc_deinit(tty);
	put_device(tty->dev);
	kfree(tty->write_buf);
	tty->magic = 0xDEADDEAD;
	kfree(tty);
}