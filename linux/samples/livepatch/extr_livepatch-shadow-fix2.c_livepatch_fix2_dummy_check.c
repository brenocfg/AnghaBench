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
struct dummy {int /*<<< orphan*/  jiffies_expire; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  SV_COUNTER ; 
 int* klp_shadow_get_or_alloc (struct dummy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int time_after (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool livepatch_fix2_dummy_check(struct dummy *d, unsigned long jiffies)
{
	int *shadow_count;

	/*
	 * Patch: handle in-flight dummy structures, if they do not
	 * already have a SV_COUNTER shadow variable, then attach a
	 * new one.
	 */
	shadow_count = klp_shadow_get_or_alloc(d, SV_COUNTER,
				sizeof(*shadow_count), GFP_NOWAIT,
				NULL, NULL);
	if (shadow_count)
		*shadow_count += 1;

	return time_after(jiffies, d->jiffies_expire);
}