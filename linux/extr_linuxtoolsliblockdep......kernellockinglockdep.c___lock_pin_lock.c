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
struct task_struct {int lockdep_depth; struct held_lock* held_locks; } ;
struct pin_cookie {int val; } ;
struct lockdep_map {int dummy; } ;
struct held_lock {int pin_count; } ;

/* Variables and functions */
 struct pin_cookie NIL_COOKIE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  debug_locks ; 
 scalar_t__ match_held_lock (struct held_lock*,struct lockdep_map*) ; 
 int prandom_u32 () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct pin_cookie __lock_pin_lock(struct lockdep_map *lock)
{
	struct pin_cookie cookie = NIL_COOKIE;
	struct task_struct *curr = current;
	int i;

	if (unlikely(!debug_locks))
		return cookie;

	for (i = 0; i < curr->lockdep_depth; i++) {
		struct held_lock *hlock = curr->held_locks + i;

		if (match_held_lock(hlock, lock)) {
			/*
			 * Grab 16bits of randomness; this is sufficient to not
			 * be guessable and still allows some pin nesting in
			 * our u32 pin_count.
			 */
			cookie.val = 1 + (prandom_u32() >> 16);
			hlock->pin_count += cookie.val;
			return cookie;
		}
	}

	WARN(1, "pinning an unheld lock\n");
	return cookie;
}