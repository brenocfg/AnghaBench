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
typedef  scalar_t__ u64 ;
struct lock_stat {scalar_t__ wait_time_min; } ;

/* Variables and functions */
 scalar_t__ ULLONG_MAX ; 

__attribute__((used)) static int lock_stat_key_wait_time_min(struct lock_stat *one,
					struct lock_stat *two)
{
	u64 s1 = one->wait_time_min;
	u64 s2 = two->wait_time_min;
	if (s1 == ULLONG_MAX)
		s1 = 0;
	if (s2 == ULLONG_MAX)
		s2 = 0;
	return s1 > s2;
}