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
struct static_key {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATIC_KEY_CHECK_USE (struct static_key*) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jump_label_lock () ; 
 int /*<<< orphan*/  jump_label_unlock () ; 
 int /*<<< orphan*/  jump_label_update (struct static_key*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lockdep_assert_cpus_held () ; 

void static_key_slow_inc_cpuslocked(struct static_key *key)
{
	int v, v1;

	STATIC_KEY_CHECK_USE(key);
	lockdep_assert_cpus_held();

	/*
	 * Careful if we get concurrent static_key_slow_inc() calls;
	 * later calls must wait for the first one to _finish_ the
	 * jump_label_update() process.  At the same time, however,
	 * the jump_label_update() call below wants to see
	 * static_key_enabled(&key) for jumps to be updated properly.
	 *
	 * So give a special meaning to negative key->enabled: it sends
	 * static_key_slow_inc() down the slow path, and it is non-zero
	 * so it counts as "enabled" in jump_label_update().  Note that
	 * atomic_inc_unless_negative() checks >= 0, so roll our own.
	 */
	for (v = atomic_read(&key->enabled); v > 0; v = v1) {
		v1 = atomic_cmpxchg(&key->enabled, v, v + 1);
		if (likely(v1 == v))
			return;
	}

	jump_label_lock();
	if (atomic_read(&key->enabled) == 0) {
		atomic_set(&key->enabled, -1);
		jump_label_update(key);
		/*
		 * Ensure that if the above cmpxchg loop observes our positive
		 * value, it must also observe all the text changes.
		 */
		atomic_set_release(&key->enabled, 1);
	} else {
		atomic_inc(&key->enabled);
	}
	jump_label_unlock();
}