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
 int atomic_read (int /*<<< orphan*/ *) ; 

int static_key_count(struct static_key *key)
{
	/*
	 * -1 means the first static_key_slow_inc() is in progress.
	 *  static_key_enabled() must return true, so return 1 here.
	 */
	int n = atomic_read(&key->enabled);

	return n >= 0 ? n : 1;
}