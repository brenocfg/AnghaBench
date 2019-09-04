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
typedef  int /*<<< orphan*/  uint ;
struct un_t {int un_flags; int /*<<< orphan*/  un_flags_wait; struct channel_t* un_ch; } ;
struct tty_struct {scalar_t__ driver_data; } ;
struct channel_t {int /*<<< orphan*/  ch_lock; } ;

/* Variables and functions */
 int ENXIO ; 
 int UN_EMPTY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cls_drain(struct tty_struct *tty, uint seconds)
{
	unsigned long flags;
	struct channel_t *ch;
	struct un_t *un;

	if (!tty)
		return -ENXIO;

	un = (struct un_t *)tty->driver_data;
	if (!un)
		return -ENXIO;

	ch = un->un_ch;
	if (!ch)
		return -ENXIO;

	spin_lock_irqsave(&ch->ch_lock, flags);
	un->un_flags |= UN_EMPTY;
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	/* NOTE: Do something with time passed in. */

	/* If ret is non-zero, user ctrl-c'ed us */

	return wait_event_interruptible(un->un_flags_wait,
					 ((un->un_flags & UN_EMPTY) == 0));
}