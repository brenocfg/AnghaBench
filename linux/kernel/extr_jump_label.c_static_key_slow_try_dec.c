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
 int /*<<< orphan*/  WARN (int,char*) ; 
 int atomic_fetch_add_unless (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static bool static_key_slow_try_dec(struct static_key *key)
{
	int val;

	val = atomic_fetch_add_unless(&key->enabled, -1, 1);
	if (val == 1)
		return false;

	/*
	 * The negative count check is valid even when a negative
	 * key->enabled is in use by static_key_slow_inc(); a
	 * __static_key_slow_dec() before the first static_key_slow_inc()
	 * returns is unbalanced, because all other static_key_slow_inc()
	 * instances block while the update is in progress.
	 */
	WARN(val < 0, "jump label: negative count!\n");
	return true;
}