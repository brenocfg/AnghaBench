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
struct TYPE_3__ {struct clocksource* clock; } ;
struct timekeeper {TYPE_1__ tkr_mono; } ;
struct clocksource {scalar_t__ (* enable ) (struct clocksource*) ;int /*<<< orphan*/  owner; int /*<<< orphan*/  (* disable ) (struct clocksource*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  seq; struct timekeeper timekeeper; } ;

/* Variables and functions */
 int TK_CLEAR_NTP ; 
 int TK_CLOCK_WAS_SET ; 
 int TK_MIRROR ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct clocksource*) ; 
 int /*<<< orphan*/  stub2 (struct clocksource*) ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_forward_now (struct timekeeper*) ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int) ; 
 TYPE_2__ tk_core ; 
 int /*<<< orphan*/  tk_setup_internals (struct timekeeper*,struct clocksource*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int change_clocksource(void *data)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	struct clocksource *new, *old;
	unsigned long flags;

	new = (struct clocksource *) data;

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);

	timekeeping_forward_now(tk);
	/*
	 * If the cs is in module, get a module reference. Succeeds
	 * for built-in code (owner == NULL) as well.
	 */
	if (try_module_get(new->owner)) {
		if (!new->enable || new->enable(new) == 0) {
			old = tk->tkr_mono.clock;
			tk_setup_internals(tk, new);
			if (old->disable)
				old->disable(old);
			module_put(old->owner);
		} else {
			module_put(new->owner);
		}
	}
	timekeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	return 0;
}