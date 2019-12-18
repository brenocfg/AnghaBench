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
struct cfg80211_registered_device {scalar_t__ cookie_counter; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static inline u64 cfg80211_assign_cookie(struct cfg80211_registered_device *rdev)
{
	u64 r = ++rdev->cookie_counter;

	if (WARN_ON(r == 0))
		r = ++rdev->cookie_counter;

	return r;
}