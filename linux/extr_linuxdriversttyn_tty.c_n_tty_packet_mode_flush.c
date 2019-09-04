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
struct tty_struct {TYPE_1__* link; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  ctrl_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_wait; scalar_t__ packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCPKT_FLUSHREAD ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_tty_packet_mode_flush(struct tty_struct *tty)
{
	unsigned long flags;

	if (tty->link->packet) {
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		tty->ctrl_status |= TIOCPKT_FLUSHREAD;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		wake_up_interruptible(&tty->link->read_wait);
	}
}