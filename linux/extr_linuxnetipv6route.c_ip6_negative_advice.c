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
struct rt6_info {int rt6i_flags; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int RTF_CACHE ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rt6_check_expired (struct rt6_info*) ; 
 int /*<<< orphan*/  rt6_remove_exception_rt (struct rt6_info*) ; 

__attribute__((used)) static struct dst_entry *ip6_negative_advice(struct dst_entry *dst)
{
	struct rt6_info *rt = (struct rt6_info *) dst;

	if (rt) {
		if (rt->rt6i_flags & RTF_CACHE) {
			rcu_read_lock();
			if (rt6_check_expired(rt)) {
				rt6_remove_exception_rt(rt);
				dst = NULL;
			}
			rcu_read_unlock();
		} else {
			dst_release(dst);
			dst = NULL;
		}
	}
	return dst;
}