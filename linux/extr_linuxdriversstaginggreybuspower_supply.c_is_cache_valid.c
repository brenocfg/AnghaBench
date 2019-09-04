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
struct gb_power_supply {scalar_t__ last_update; scalar_t__ cache_invalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_time ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_after_jiffies (scalar_t__) ; 

__attribute__((used)) static int is_cache_valid(struct gb_power_supply *gbpsy)
{
	/* check if cache is good enough or it has expired */
	if (gbpsy->cache_invalid) {
		gbpsy->cache_invalid = 0;
		return 0;
	}

	if (gbpsy->last_update &&
	    time_is_after_jiffies(gbpsy->last_update +
				  msecs_to_jiffies(cache_time)))
		return 1;

	return 0;
}