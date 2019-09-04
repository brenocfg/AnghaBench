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
typedef  scalar_t__ u32 ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ fib6_check_expired (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_get_cookie_safe (struct fib6_info*,scalar_t__*) ; 

__attribute__((used)) static bool fib6_check(struct fib6_info *f6i, u32 cookie)
{
	u32 rt_cookie = 0;

	if (!fib6_get_cookie_safe(f6i, &rt_cookie) || rt_cookie != cookie)
		return false;

	if (fib6_check_expired(f6i))
		return false;

	return true;
}