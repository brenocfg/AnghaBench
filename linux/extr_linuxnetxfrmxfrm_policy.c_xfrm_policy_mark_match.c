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
typedef  int u32 ;
struct TYPE_2__ {int v; int m; } ;
struct xfrm_policy {scalar_t__ priority; TYPE_1__ mark; } ;

/* Variables and functions */

__attribute__((used)) static bool xfrm_policy_mark_match(struct xfrm_policy *policy,
				   struct xfrm_policy *pol)
{
	u32 mark = policy->mark.v & policy->mark.m;

	if (policy->mark.v == pol->mark.v && policy->mark.m == pol->mark.m)
		return true;

	if ((mark & pol->mark.m) == pol->mark.v &&
	    policy->priority == pol->priority)
		return true;

	return false;
}