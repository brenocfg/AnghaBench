#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  all; } ;
struct xfrm_policy {TYPE_1__ walk; } ;
struct TYPE_4__ {int /*<<< orphan*/ * policy_count; int /*<<< orphan*/  policy_all; } ;
struct net {TYPE_2__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static void __xfrm_policy_link(struct xfrm_policy *pol, int dir)
{
	struct net *net = xp_net(pol);

	list_add(&pol->walk.all, &net->xfrm.policy_all);
	net->xfrm.policy_count[dir]++;
	xfrm_pol_hold(pol);
}