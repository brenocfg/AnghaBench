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
struct tty_struct {int /*<<< orphan*/  flow_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void start_tty(struct tty_struct *tty)
{
	unsigned long flags;

	spin_lock_irqsave(&tty->flow_lock, flags);
	__start_tty(tty);
	spin_unlock_irqrestore(&tty->flow_lock, flags);
}