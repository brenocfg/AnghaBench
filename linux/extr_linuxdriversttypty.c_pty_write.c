#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* port; scalar_t__ stopped; struct tty_struct* link; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (TYPE_1__*) ; 
 int tty_insert_flip_string (TYPE_1__*,unsigned char const*,int) ; 

__attribute__((used)) static int pty_write(struct tty_struct *tty, const unsigned char *buf, int c)
{
	struct tty_struct *to = tty->link;
	unsigned long flags;

	if (tty->stopped)
		return 0;

	if (c > 0) {
		spin_lock_irqsave(&to->port->lock, flags);
		/* Stuff the data into the input queue of the other end */
		c = tty_insert_flip_string(to->port, buf, c);
		/* And shovel */
		if (c)
			tty_flip_buffer_push(to->port);
		spin_unlock_irqrestore(&to->port->lock, flags);
	}
	return c;
}