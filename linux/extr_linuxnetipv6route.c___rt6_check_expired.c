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
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct rt6_info {int rt6i_flags; TYPE_1__ dst; } ;

/* Variables and functions */
 int RTF_EXPIRES ; 
 int /*<<< orphan*/  jiffies ; 
 int time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __rt6_check_expired(const struct rt6_info *rt)
{
	if (rt->rt6i_flags & RTF_EXPIRES)
		return time_after(jiffies, rt->dst.expires);
	else
		return false;
}