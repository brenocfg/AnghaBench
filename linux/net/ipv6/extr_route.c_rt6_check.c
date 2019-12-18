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
struct dst_entry {int dummy; } ;
struct rt6_info {struct dst_entry dst; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_get_cookie_safe (struct fib6_info*,scalar_t__*) ; 
 scalar_t__ rt6_check_expired (struct rt6_info*) ; 

__attribute__((used)) static struct dst_entry *rt6_check(struct rt6_info *rt,
				   struct fib6_info *from,
				   u32 cookie)
{
	u32 rt_cookie = 0;

	if (!from || !fib6_get_cookie_safe(from, &rt_cookie) ||
	    rt_cookie != cookie)
		return NULL;

	if (rt6_check_expired(rt))
		return NULL;

	return &rt->dst;
}