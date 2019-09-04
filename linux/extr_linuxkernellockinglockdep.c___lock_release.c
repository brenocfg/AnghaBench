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
struct task_struct {unsigned int lockdep_depth; int /*<<< orphan*/  curr_chain_key; } ;
struct lockdep_map {int dummy; } ;
struct held_lock {int /*<<< orphan*/  prev_chain_key; scalar_t__ references; int /*<<< orphan*/  pin_count; struct lockdep_map* instance; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  debug_locks ; 
 struct held_lock* find_held_lock (struct task_struct*,struct lockdep_map*,unsigned int,int*) ; 
 int /*<<< orphan*/  lock_release_holdtime (struct held_lock*) ; 
 int print_unlock_imbalance_bug (struct task_struct*,struct lockdep_map*,unsigned long) ; 
 scalar_t__ reacquire_held_locks (struct task_struct*,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
__lock_release(struct lockdep_map *lock, int nested, unsigned long ip)
{
	struct task_struct *curr = current;
	struct held_lock *hlock;
	unsigned int depth;
	int i;

	if (unlikely(!debug_locks))
		return 0;

	depth = curr->lockdep_depth;
	/*
	 * So we're all set to release this lock.. wait what lock? We don't
	 * own any locks, you've been drinking again?
	 */
	if (DEBUG_LOCKS_WARN_ON(depth <= 0))
		 return print_unlock_imbalance_bug(curr, lock, ip);

	/*
	 * Check whether the lock exists in the current stack
	 * of held locks:
	 */
	hlock = find_held_lock(curr, lock, depth, &i);
	if (!hlock)
		return print_unlock_imbalance_bug(curr, lock, ip);

	if (hlock->instance == lock)
		lock_release_holdtime(hlock);

	WARN(hlock->pin_count, "releasing a pinned lock\n");

	if (hlock->references) {
		hlock->references--;
		if (hlock->references) {
			/*
			 * We had, and after removing one, still have
			 * references, the current lock stack is still
			 * valid. We're done!
			 */
			return 1;
		}
	}

	/*
	 * We have the right lock to unlock, 'hlock' points to it.
	 * Now we remove it from the stack, and add back the other
	 * entries (if any), recalculating the hash along the way:
	 */

	curr->lockdep_depth = i;
	curr->curr_chain_key = hlock->prev_chain_key;

	if (reacquire_held_locks(curr, depth, i + 1))
		return 0;

	/*
	 * We had N bottles of beer on the wall, we drank one, but now
	 * there's not N-1 bottles of beer left on the wall...
	 */
	if (DEBUG_LOCKS_WARN_ON(curr->lockdep_depth != depth - 1))
		return 0;

	return 1;
}