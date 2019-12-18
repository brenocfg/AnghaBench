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
struct timer_list {int flags; int /*<<< orphan*/  function; } ;
struct timer_base {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int TIMER_BASEMASK ; 
 int TIMER_MIGRATING ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  debug_timer_activate (struct timer_list*) ; 
 int /*<<< orphan*/  forward_timer_base (struct timer_base*) ; 
 struct timer_base* get_timer_cpu_base (int,int) ; 
 int /*<<< orphan*/  internal_add_timer (struct timer_base*,struct timer_list*) ; 
 struct timer_base* lock_timer_base (struct timer_list*,unsigned long*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_pending (struct timer_list*) ; 

void add_timer_on(struct timer_list *timer, int cpu)
{
	struct timer_base *new_base, *base;
	unsigned long flags;

	BUG_ON(timer_pending(timer) || !timer->function);

	new_base = get_timer_cpu_base(timer->flags, cpu);

	/*
	 * If @timer was on a different CPU, it should be migrated with the
	 * old base locked to prevent other operations proceeding with the
	 * wrong base locked.  See lock_timer_base().
	 */
	base = lock_timer_base(timer, &flags);
	if (base != new_base) {
		timer->flags |= TIMER_MIGRATING;

		raw_spin_unlock(&base->lock);
		base = new_base;
		raw_spin_lock(&base->lock);
		WRITE_ONCE(timer->flags,
			   (timer->flags & ~TIMER_BASEMASK) | cpu);
	}
	forward_timer_base(base);

	debug_timer_activate(timer);
	internal_add_timer(base, timer);
	raw_spin_unlock_irqrestore(&base->lock, flags);
}