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
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTIME_SEC_MAX ; 
 scalar_t__ ktime_add_unsafe (scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ktime_t ktime_add_safe(const ktime_t lhs, const ktime_t rhs)
{
	ktime_t res = ktime_add_unsafe(lhs, rhs);

	/*
	 * We use KTIME_SEC_MAX here, the maximum timeout which we can
	 * return to user space in a timespec:
	 */
	if (res < 0 || res < lhs || res < rhs)
		res = ktime_set(KTIME_SEC_MAX, 0);

	return res;
}