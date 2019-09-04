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
struct napi_struct {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 unsigned long NAPIF_STATE_DISABLE ; 
 unsigned long NAPIF_STATE_MISSED ; 
 unsigned long NAPIF_STATE_SCHED ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (unsigned long) ; 

bool napi_schedule_prep(struct napi_struct *n)
{
	unsigned long val, new;

	do {
		val = READ_ONCE(n->state);
		if (unlikely(val & NAPIF_STATE_DISABLE))
			return false;
		new = val | NAPIF_STATE_SCHED;

		/* Sets STATE_MISSED bit if STATE_SCHED was already set
		 * This was suggested by Alexander Duyck, as compiler
		 * emits better code than :
		 * if (val & NAPIF_STATE_SCHED)
		 *     new |= NAPIF_STATE_MISSED;
		 */
		new |= (val & NAPIF_STATE_SCHED) / NAPIF_STATE_SCHED *
						   NAPIF_STATE_MISSED;
	} while (cmpxchg(&n->state, val, new) != val);

	return !(val & NAPIF_STATE_SCHED);
}