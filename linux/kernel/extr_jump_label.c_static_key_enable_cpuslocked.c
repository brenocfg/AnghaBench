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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jump_label_lock () ; 
 int /*<<< orphan*/  jump_label_unlock () ; 
 int /*<<< orphan*/  jump_label_update (struct static_key*) ; 
 int /*<<< orphan*/  lockdep_assert_cpus_held () ; 

void static_key_enable_cpuslocked(struct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	lockdep_assert_cpus_held();

	if (atomic_read(&key->enabled) > 0) {
		WARN_ON_ONCE(atomic_read(&key->enabled) != 1);
		return;
	}

	jump_label_lock();
	if (atomic_read(&key->enabled) == 0) {
		atomic_set(&key->enabled, -1);
		jump_label_update(key);
		/*
		 * See static_key_slow_inc().
		 */
		atomic_set_release(&key->enabled, 1);
	}
	jump_label_unlock();
}