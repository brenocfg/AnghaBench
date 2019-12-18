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
struct rt6_info {int rt6i_flags; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int RTF_CACHE ; 
 int RTF_PCPU ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rt6_cache_allowed_for_pmtu(const struct rt6_info *rt)
{
	return !(rt->rt6i_flags & RTF_CACHE) &&
		(rt->rt6i_flags & RTF_PCPU || rcu_access_pointer(rt->from));
}