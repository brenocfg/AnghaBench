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
typedef  int /*<<< orphan*/  u64 ;
struct net {int dummy; } ;
typedef  enum nsim_resource_id { ____Placeholder_nsim_resource_id } nsim_resource_id ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int NSIM_RESOURCE_IPV4_FIB ; 
 int NSIM_RESOURCE_IPV4_FIB_RULES ; 
 int NSIM_RESOURCE_IPV6_FIB ; 
 int NSIM_RESOURCE_IPV6_FIB_RULES ; 
 scalar_t__ nsim_fib_set_max (struct net*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void nsim_devlink_net_reset(struct net *net)
{
	enum nsim_resource_id res_ids[] = {
		NSIM_RESOURCE_IPV4_FIB, NSIM_RESOURCE_IPV4_FIB_RULES,
		NSIM_RESOURCE_IPV6_FIB, NSIM_RESOURCE_IPV6_FIB_RULES
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(res_ids); ++i) {
		if (nsim_fib_set_max(net, res_ids[i], (u64)-1, NULL)) {
			pr_err("Failed to reset limit for resource %u\n",
			       res_ids[i]);
		}
	}
}