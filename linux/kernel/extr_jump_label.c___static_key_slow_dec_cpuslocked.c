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
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jump_label_lock () ; 
 int /*<<< orphan*/  jump_label_unlock () ; 
 int /*<<< orphan*/  jump_label_update (struct static_key*) ; 
 int /*<<< orphan*/  lockdep_assert_cpus_held () ; 
 scalar_t__ static_key_slow_try_dec (struct static_key*) ; 

__attribute__((used)) static void __static_key_slow_dec_cpuslocked(struct static_key *key)
{
	lockdep_assert_cpus_held();

	if (static_key_slow_try_dec(key))
		return;

	jump_label_lock();
	if (atomic_dec_and_test(&key->enabled))
		jump_label_update(key);
	jump_label_unlock();
}