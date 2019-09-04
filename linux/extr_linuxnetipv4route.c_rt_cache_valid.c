#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ obsolete; } ;
struct rtable {TYPE_1__ dst; } ;

/* Variables and functions */
 scalar_t__ DST_OBSOLETE_FORCE_CHK ; 
 int /*<<< orphan*/  rt_is_expired (struct rtable const*) ; 

__attribute__((used)) static bool rt_cache_valid(const struct rtable *rt)
{
	return	rt &&
		rt->dst.obsolete == DST_OBSOLETE_FORCE_CHK &&
		!rt_is_expired(rt);
}