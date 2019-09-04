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
struct xfrm_policy_walk {int dummy; } ;
struct netlink_callback {scalar_t__ args; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_ANY ; 
 int /*<<< orphan*/  xfrm_policy_walk_init (struct xfrm_policy_walk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_dump_policy_start(struct netlink_callback *cb)
{
	struct xfrm_policy_walk *walk = (struct xfrm_policy_walk *)cb->args;

	BUILD_BUG_ON(sizeof(*walk) > sizeof(cb->args));

	xfrm_policy_walk_init(walk, XFRM_POLICY_TYPE_ANY);
	return 0;
}