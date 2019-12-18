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
typedef  scalar_t__ time_t ;
struct cache_head {int /*<<< orphan*/  flags; scalar_t__ last_refresh; scalar_t__ expiry_time; } ;
struct cache_detail {scalar_t__ flush_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_VALID ; 
 scalar_t__ seconds_since_boot () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void cache_fresh_locked(struct cache_head *head, time_t expiry,
			       struct cache_detail *detail)
{
	time_t now = seconds_since_boot();
	if (now <= detail->flush_time)
		/* ensure it isn't immediately treated as expired */
		now = detail->flush_time + 1;
	head->expiry_time = expiry;
	head->last_refresh = now;
	smp_wmb(); /* paired with smp_rmb() in cache_is_valid() */
	set_bit(CACHE_VALID, &head->flags);
}