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
struct held_lock {int read; unsigned long acquire_ip; int /*<<< orphan*/  prev_chain_key; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct task_struct* current ; 
 struct held_lock* find_held_lock (struct task_struct*,struct lockdep_map*,unsigned int,int*) ; 
 int print_unlock_imbalance_bug (struct task_struct*,struct lockdep_map*,unsigned long) ; 
 scalar_t__ reacquire_held_locks (struct task_struct*,unsigned int,int) ; 

__attribute__((used)) static int __lock_downgrade(struct lockdep_map *lock, unsigned long ip)
{
	struct task_struct *curr = current;
	struct held_lock *hlock;
	unsigned int depth;
	int i;

	depth = curr->lockdep_depth;
	/*
	 * This function is about (re)setting the class of a held lock,
	 * yet we're not actually holding any locks. Naughty user!
	 */
	if (DEBUG_LOCKS_WARN_ON(!depth))
		return 0;

	hlock = find_held_lock(curr, lock, depth, &i);
	if (!hlock)
		return print_unlock_imbalance_bug(curr, lock, ip);

	curr->lockdep_depth = i;
	curr->curr_chain_key = hlock->prev_chain_key;

	WARN(hlock->read, "downgrading a read lock");
	hlock->read = 1;
	hlock->acquire_ip = ip;

	if (reacquire_held_locks(curr, depth, i))
		return 0;

	/*
	 * I took it apart and put it back together again, except now I have
	 * these 'spare' parts.. where shall I put them.
	 */
	if (DEBUG_LOCKS_WARN_ON(curr->lockdep_depth != depth))
		return 0;
	return 1;
}