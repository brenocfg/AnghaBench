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

/* Variables and functions */
 int /*<<< orphan*/  netstamp_needed_key ; 
 int /*<<< orphan*/  static_branch_dec (int /*<<< orphan*/ *) ; 

void net_disable_timestamp(void)
{
#ifdef HAVE_JUMP_LABEL
	int wanted;

	while (1) {
		wanted = atomic_read(&netstamp_wanted);
		if (wanted <= 1)
			break;
		if (atomic_cmpxchg(&netstamp_wanted, wanted, wanted - 1) == wanted)
			return;
	}
	atomic_dec(&netstamp_needed_deferred);
	schedule_work(&netstamp_work);
#else
	static_branch_dec(&netstamp_needed_key);
#endif
}