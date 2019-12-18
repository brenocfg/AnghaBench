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
struct net_device {scalar_t__ group; } ;
struct fib_rule {scalar_t__ suppress_prefixlen; int suppress_ifgroup; } ;
struct fib_result {scalar_t__ prefixlen; scalar_t__ fi; } ;
struct fib_nh_common {struct net_device* nhc_dev; } ;
struct fib_lookup_arg {int flags; scalar_t__ result; } ;

/* Variables and functions */
 int FIB_LOOKUP_NOREF ; 
 struct fib_nh_common* fib_info_nhc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_info_put (scalar_t__) ; 

__attribute__((used)) static bool fib4_rule_suppress(struct fib_rule *rule, struct fib_lookup_arg *arg)
{
	struct fib_result *result = (struct fib_result *) arg->result;
	struct net_device *dev = NULL;

	if (result->fi) {
		struct fib_nh_common *nhc = fib_info_nhc(result->fi, 0);

		dev = nhc->nhc_dev;
	}

	/* do not accept result if the route does
	 * not meet the required prefix length
	 */
	if (result->prefixlen <= rule->suppress_prefixlen)
		goto suppress_route;

	/* do not accept result if the route uses a device
	 * belonging to a forbidden interface group
	 */
	if (rule->suppress_ifgroup != -1 && dev && dev->group == rule->suppress_ifgroup)
		goto suppress_route;

	return false;

suppress_route:
	if (!(arg->flags & FIB_LOOKUP_NOREF))
		fib_info_put(result->fi);
	return true;
}